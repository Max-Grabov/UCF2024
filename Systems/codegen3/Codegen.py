import os
import sys
import math
from textwrap import indent, dedent
from antlr4 import *
from grammar.SimpleIRLexer import SimpleIRLexer
from grammar.SimpleIRParser import SimpleIRParser
from grammar.SimpleIRListener import SimpleIRListener
import logging
logging.basicConfig(level=logging.DEBUG)

# This class defines a complete listener for a parse tree produced by SimpleIRParser.
class CodeGen(SimpleIRListener):
    def __init__(self, filename, outfile):
        self.filename = filename
        self.outfile = outfile
        self.symtab = {}
        self.bitwidth = 8

    def enterLocalvars(self, ctx:SimpleIRParser.LocalvarsContext):
        """Allocates space for local variables, including input parameters"""
        # get list of local variables
        locals = [ local.getText() for local in ctx.NAME() ]
        # create a list of offsets of the bitwidth
        offsets = map(lambda x: (x+1)*-self.bitwidth, range(len(locals)))
        # create a dictionary mapping locals to offsets
        self.symtab = dict(zip(locals, offsets))
        logging.debug(self.symtab)
        # compute the size of the stack space
        stackspace = len(self.symtab.keys()) * self.bitwidth
        logging.debug(stackspace)
        # ceiling to 8 bytes
        stackoffset = math.ceil(stackspace / 8) * 8
        # align to 16 bytes by adding 8 to account for rbx if already aligned to 16 bytes
        stackoffset += (stackoffset + 8) % 16
        logging.debug(stackoffset)
        # Emit an instruction to allocate stack space for locals
        self.outfile.write(indent(dedent(f'''\
            # allocate stack space for locals
            sub\t${stackoffset}, %rsp
        '''), '\t'))

    def enterAssign(self, ctx:SimpleIRParser.AssignContext):
        """Assign value to a variable"""
        if SimpleIRParser.NAME == ctx.operand.type:
            operand = f"{self.symtab[ctx.operand.text]}(%rbp)"
        elif SimpleIRParser.NUM == ctx.operand.type:
            operand = f"${ctx.operand.text}"
        self.outfile.write(indent(dedent(f'''\
            # assign {ctx.operand.text} to {ctx.NAME(0).getText()}
            mov\t{operand}, %rax
            mov\t%rax, {self.symtab[ctx.NAME(0).getText()]}(%rbp)
        '''), '\t'))

    def enterOperation(self, ctx:SimpleIRParser.OperationContext):
        """Arithmetic operation"""
        op1 = ""

        if SimpleIRParser.NAME == ctx.op1.type:
            op1 = f"{self.symtab[ctx.op1.text]}(%rbp)"

        elif SimpleIRParser.NUM == ctx.op1.type:
            op1 = f"${ctx.op1.text}"

        op2 = ""

        if SimpleIRParser.NAME == ctx.op2.type:
            op2 = f"{self.symtab[ctx.op2.text]}(%rbp)"

        elif SimpleIRParser.NUM == ctx.op2.type:
            op2 = f"${ctx.op2.text}"


        self.outfile.write(f"\tmov\t{op1}, %rax\n")
        self.outfile.write(f"\tmov\t{op2}, %rbx\n")

        if SimpleIRParser.PLUS == ctx.operator.type:
            self.outfile.write("\tadd\t%rbx, %rax\n")

        elif SimpleIRParser.MINUS == ctx.operator.type:
            self.outfile.write("\tsub\t%rbx, %rax\n")

        elif SimpleIRParser.STAR == ctx.operator.type:
            self.outfile.write("\timul\t%rbx, %rax\n")

        elif SimpleIRParser.SLASH == ctx.operator.type:
            self.outfile.write("\tcdq\n")
            self.outfile.write("\tidiv %rbx\n")

        elif SimpleIRParser.PERCENT == ctx.operator.type:
            self.outfile.write("\tcdq\n")
            self.outfile.write("\tidiv %rbx\n")
            self.outfile.write("\tmov\t%rdx, %rax\n")

        destination = f"{self.symtab[ctx.NAME(0).getText()]}(%rbp)"

        self.outfile.write(f"\tmov\t%rax, {destination}\n")


    def enterLabel(self, ctx:SimpleIRParser.LabelContext):
        """Create a label"""
        self.outfile.write(f"{ctx.NAME()}:\n")

    def enterGoto(self, ctx:SimpleIRParser.GotoContext):
        """Unconditional goto"""
        self.outfile.write(f"\tjmp {ctx.NAME()}\n")

    def enterIfgoto(self, ctx:SimpleIRParser.IfgotoContext):
        """Conditional goto"""

        op1 = ""

        if SimpleIRParser.NAME == ctx.op1.type:
            op1 = f"{self.symtab[ctx.op1.text]}(%rbp)"

        elif SimpleIRParser.NUM == ctx.op1.type:
            op1 = f"${ctx.op1.text}"

        op2 = ""

        if SimpleIRParser.NAME == ctx.op2.type:
            op2 = f"{self.symtab[ctx.op2.text]}(%rbp)"

        elif SimpleIRParser.NUM == ctx.op2.type:
            op2 = f"${ctx.op2.text}"

        self.outfile.write(f"\tmov\t{op1}, %rax\n")
        self.outfile.write(f"\tmov\t{op2}, %rbx\n")
        self.outfile.write(f"\tcmp\t%rbx, %rax\n")

        jump = ""
        if SimpleIRParser.EQ == ctx.operator.type:
            jump = "je"

        elif SimpleIRParser.LTE == ctx.operator.type:
            jump = "jle"

        elif SimpleIRParser.GTE == ctx.operator.type:
            jump = "jge"

        elif SimpleIRParser.NEQ == ctx.operator.type:
            jump = "jne"

        elif SimpleIRParser.LT == ctx.operator.type:
            jump = "jl"

        elif SimpleIRParser.GT == ctx.operator.type:
            jump = "jg"


        self.outfile.write(f"\t{jump}\t{ctx.labelname.text}\n")

def main():
    import sys
    if len(sys.argv) > 1:
        filepath = sys.argv[1]
        input_stream = FileStream(filepath)
        filename = os.path.basename(filepath)
    else:
        input_stream = StdinStream()
        filename = "stdin"

    lexer = SimpleIRLexer(input_stream)
    stream = CommonTokenStream(lexer)
    parser = SimpleIRParser(stream)
    tree = parser.unit()
    if parser.getNumberOfSyntaxErrors() > 0:
        print("syntax errors")
        exit(1)
    # print(tree.toStringTree())
    walker = ParseTreeWalker()
    walker.walk(CodeGen(filename, sys.stdout), tree)

if __name__ == '__main__':
    main()