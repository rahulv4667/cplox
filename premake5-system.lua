-- buildmessage "Compiling Tool/generator_ast.py"
-- prebuildcommands {
--     "python3 Tool/generate_ast.py"
-- }
-- buildoutputs {"./include/Parser/Expr.hpp", "./src/Parser/Expr.cpp"}
os.execute('python3 Tool/generate_ast.py')