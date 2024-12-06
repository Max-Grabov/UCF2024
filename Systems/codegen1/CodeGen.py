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

    def enterReturn(self, ctx:SimpleIRParser.ReturnContext):
        """Sets the return value"""
        self.outfile.write(
            f'''mov  \t${ctx.operand.text}, %rax\n'''
        )

    def enterCall(self, ctx:SimpleIRParser.CallContext):
        """Function call"""
        call = [name.getText() for name in ctx.NAME()]
        self.outfile.write(
            f'''call \t{call[1]}\n'''
        )


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