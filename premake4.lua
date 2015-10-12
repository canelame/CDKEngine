-- Create Solution

solution "SolutionTestGenie"

configurations{"Debug","Release"}
location("debug")
targetdir("debug/bin")
debugdir("debug/bin")


project "ProjectTestGenie"
kind "ConsoleApp"
language "C++"
defines {"_GLFW_WIN32","_GLFW_WGL","_GLFW_USE_OPENGL","GLEW_STATIC"}
links{"opengl32"}
includedirs{"include","include/**"}
files{"include/**.h","src/**.cc","src/**.c"}
configuration "Debug"

flags "Symbols"