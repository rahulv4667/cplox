import sys
import os


def template_str(c: str = 'T'):
    return f'template<typename {c}>'


def initialize_params(src_lines: list, params: str):
    comma_sep_params = params.split(',')
    for param in comma_sep_params:
        param_def = param.split(' ')

        # last of `param_def` is the variable name
        src_lines.append(f'\t\t{param_def[-1]}({param_def[-1]}),')

    # removing comma after initializing last parameter.
    src_lines[-1] = src_lines[-1][:-1]

def define_params(header_lines: list, class_name: str, params: str):
    comma_sep_params = params.split(',')
    for param in comma_sep_params:
        header_lines.append(f'\t\t{param};')


def define_subtypes(header_lines: list, base_name: str, types: list):
    header_lines.append('\t\tpublic:')
    for type in types:
        [class_name, params] = type.split(':')
        class_name = class_name.strip()
        header_lines.append(f'\t\t\tclass {class_name};')

def define_const_dest(header_lines: list, base_name:str):
    # adding public destructor
    header_lines.append('\t\tpublic:')
    header_lines.append(f'\t\t\tvirtual ~{base_name}() = default;')

    # adding private constructor to make the class virtual
    # without having additional methods.
    header_lines.append('\t\tprotected:')
    header_lines.append(f'\t\t\t{base_name}() = default;')

def define_each_subtype(header_lines: list, base_name: str, types: list):
    for type in types:
        [class_name, params] = type.split(':')
        class_name = class_name.strip()

        # starting subtype class
        header_lines.append(f'\tclass {base_name}::{class_name} : public {base_name} {{')
        define_params(header_lines, class_name, params)

        # define subtype constructor
        header_lines.append('\t\tpublic:')
        header_lines.append(f'\t\t\t{class_name}({params});')
        header_lines.append(f'\n\t\t\t{template_str()}')
        header_lines.append(f'\t\t\tT accept(Visitor<T> visitor) override;')

        header_lines.append('\t};\n')

def define_visitor_hpp(header_lines: list, base_name: str, types: list):
    header_lines.append(f'\t{template_str()}')
    header_lines.append(f'\tclass {base_name}::Visitor {{')
    header_lines.append(f'\t\tpublic:')
    for type in types:
        [class_name, _] = type.split(':')
        class_name = class_name.strip()
        header_lines.append(f'\t\t\tvirtual T visit({base_name}::{class_name}& {class_name.lower()});')
    header_lines.append('\t};\n')


def define_visitor_in_class(header_lines: list, base_name: str, types: list):
    header_lines.append('\t\tpublic:')
    header_lines.append(f'\t\t\t{template_str()}')
    header_lines.append(f'\t\t\tclass Visitor;')
    header_lines.append(f'\t\t\t{template_str()}')
    header_lines.append(f'\t\t\tT accept(Visitor<T> visitor);')


def implement_subtypes(src_lines: list, base_name: str, types: list):
    for type in types:
        [class_name, params] = type.split(':')
        class_name = class_name.strip()

        # constructor
        src_lines.append(f'\t{base_name}::{class_name}::{class_name}({params}) : ')
        initialize_params(src_lines, params)
        src_lines.append('\t {}\n')

        # accept method
        src_lines.append(f'\t{template_str()}')
        src_lines.append(f'\tT {base_name}::{class_name}::accept(Visitor<T> visitor) {{')
        src_lines.append(f'\t\treturn visitor.visit(*this);')
        src_lines.append(f'\t}}\n')


def define_ast(header_dir: str, src_dir: str, base_name: str, types: list):
    try:
        header_path = header_dir + '/Parser/' + base_name + '.hpp'
        src_path = src_dir + '/Parser/' + base_name + '.cpp'

        header_lines = list()
        src_lines = list()

        header_lines.append('#include <Scanner/LiteralType.hpp>')
        header_lines.append('#include <Scanner/Token.hpp>')
        src_lines.append(f'#include <Parser/{base_name}.hpp>')

        # starting namespace
        header_lines.append('namespace Lox {')
        src_lines.append('namespace Lox {')

        # starting base class
        header_lines.append(f'\tclass {base_name} {{')
        define_subtypes(header_lines, base_name, types)
        define_const_dest(header_lines=header_lines, base_name=base_name)

        # declaring visitor inside base class
        define_visitor_in_class(header_lines, base_name, types)
        
        #closing base class
        header_lines.append('\t};\n')

        # defining class for each subtype.
        define_each_subtype(header_lines=header_lines, base_name=base_name, types=types)

        # defining visitor class in hpp
        define_visitor_hpp(header_lines, base_name, types)


        ##############################
        ####### Defining src #########
        ##############################
        implement_subtypes(src_lines, base_name, types)

        # closing namespace
        header_lines.append('\t}')
        src_lines.append('}')

        # file handles
        header_f = open(header_path, 'w')
        src_f = open(src_path, 'w')
        
        # writing to files
        header_f.write('\n'.join(header_lines))
        src_f.write('\n'.join(src_lines))

        header_f.close()
        src_f.close()
    except Exception as e:
        print('Exception raised while generating AST: ', e)

if __name__ == "__main__":
    # if len(sys.argv) != 3:
    #     print("Usage: generate_ast.py <header directory> <source directory>")
    #     exit()
    if len(sys.argv) == 1:
        # paths relative to root
        header_dir = './include'
        src_dir = './src'
    else:
        header_dir = sys.argv[1]
        src_dir = sys.argv[2]

    print('Starting generating AST....')
    print(f'Current working directory:{os.getcwd()}')
    
    define_ast(header_dir, src_dir, "Expr", [
        "Binary     : Expr left, Token oprtr, Expr right",
        "Grouping   : Expr expression",
        "Literal    : LiteralType value",
        "Unary      : Token oprtr, Expr right"
    ])
