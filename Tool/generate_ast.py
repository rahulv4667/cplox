import sys
import os


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
    for type in types:
        [class_name, params] = type.split(':')
        header_lines.append(f'\t\tclass {class_name};')

    # adding public destructor
    header_lines.append('\t\tpublic:')
    header_lines.append(f'\t\t\tvirtual ~{base_name}() = default;')

    # adding private constructor to make the class virtual
    # without having additional methods.
    header_lines.append('\t\tprivate:')
    header_lines.append(f'\t\t\t{base_name}() = default;')

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
        
        #closing base class
        header_lines.append('\t};\n')

        # defining class for each subtype.
        for type in types:
            [class_name, params] = type.split(':')
            
            # starting subtype class
            header_lines.append(f'\tclass {base_name}::{class_name} : public {base_name} {{')
            define_params(header_lines, class_name, params)

            # define subtype constructor
            header_lines.append(f'\t\t{class_name}({params});')

            header_lines.append('\t};\n')

        ##############################
        ####### Defining src #########
        ##############################
        for type in types:
            [class_name, params] = type.split(':')

            src_lines.append(f'\t{base_name}::{class_name}::{class_name}({params}) : ')
            initialize_params(src_lines, params)
            src_lines.append('\t {}')


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
