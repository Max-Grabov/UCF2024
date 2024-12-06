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
        self.bytewidth = 8

    def enterUnit(self, ctx:SimpleIRParser.UnitContext):
        """Creates the object file sections"""
        self.outfile.write(
f'''\t.file "{self.filename}"
\t.section .note.GNU-stack,"",@progbits
\t.text
''')

    def enterLocalvars(self, ctx:SimpleIRParser.LocalvarsContext):
        """Allocates space for local variables, including input parameters"""
        # get list of local variables
        locals = [ local.getText() for local in ctx.NAME() ]
        # create a list of offsets of the bytewidth
        offsets = map(lambda x: (x+1)*-self.bytewidth, range(len(locals)))
        # create a dictionary mapping locals to offsets
        self.symtab = dict(zip(locals, offsets))
        logging.debug(self.symtab)
        # compute the size of the stack space
        stackspace = len(self.symtab.keys()) * self.bytewidth
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

    def enterFunction(self, ctx:SimpleIRParser.FunctionContext):
        """Emits the label and prologue"""
        self.outfile.write(
            f'''\t.globl {ctx.NAME()}\n
                \t.type {ctx.NAME()}, @function\n
                {ctx.NAME()}:\n
                \t# prologue\n
                \tpushq\t%rbp\n
                \tmovq  \t%rsp, %rbp\n
                \tpush  \t%rbx\n'''
        )

    def exitFunction(self, ctx:SimpleIRParser.FunctionContext):
        """Emits the epilogue"""
        self.outfile.write(
            f'''\t# epilogueS
                \tpop  \t%rbx\n
                \tmov  \t%rbp, %rsp\n
                \tpop  \t%rbp\n
                \tret\n'''
        )

    def enterParams(self, ctx:SimpleIRParser.ParamsContext):
        """Moves input parameters to their local variables"""
        registers = ["%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"]
        params = [param.getText() for param in ctx.NAME()]

        register_params = params[0:6]
        stack_params = params[6:]

        for count, rp in enumerate(register_params):
            self.outfile.write(f"\tmov  \t{registers[count]}, {self.symtab[rp]}(%rbp)\n")

        for count, sp in enumerate(stack_params):
            self.outfile.write(f"mov {16 + count * 8}(%rbp), %rax\n")
            self.outfile.write(f"mov %rax, {self.symtab[sp]}(%rbp)\n")


    def enterReturn(self, ctx:SimpleIRParser.ReturnContext):
        """Sets the return value"""
        if ctx.operand.type == SimpleIRParser.NAME:
            self.outfile.write(f"mov {self.symtab[ctx.operand.text]}(%rbp), %rax\n")

        elif ctx.operand.type == SimpleIRParser.NUM:
            self.outfile.write(f"mov ${ctx.operand.text}, %rax\n")

    def enterCall(self, ctx:SimpleIRParser.CallContext):
        """Function call"""
        call = [name.getText() for name in ctx.NAME()]

        var_name = call[0]
        function_name = call[1]
        params = call[2:]

        registers = ["%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"]

        register_params = params[0:6]
        stack_params = params[6:]

        for count, rp in enumerate(register_params):
            self.outfile.write(f"mov {self.symtab[rp]}(%rbp), {registers[count]}\n")

        for count, sp in enumerate(stack_params):
            self.outfile.write(f"push {self.symtab[sp]}(%rbp)\n")

        self.outfile.write(f"call {function_name}\n")

        self.outfile.write(f"add ${8 * len(stack_params)}, %rsp\n")

        self.outfile.write(f"mov %rax, {self.symtab[var_name]}(%rbp)\n")

# scp C:\UCF_2024_2025\Systems\codegen2\CodeGen.py ma725080@eustis.eecs.ucf.edu:~/Systems/Codegen2
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