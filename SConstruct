import os
from sys import platform

env = Environment(ENV=os.environ)
env.Tool('compilation_db')
env.CompilationDatabase()


# Set environment
env.Append(CPPPATH = ['#', '#include'])
env.Append(CXXFLAGS = ['-O3', '-Wall', '-Wextra', '-pedantic', '-std=c++17'])
# env.Append(CXXFLAGS = ['-g', '-Wall', '-Wextra', '-pedantic', '-std=c++17'])

# Export environment
Export('env')

# Run SConscript files
SConscript('SConscript')
