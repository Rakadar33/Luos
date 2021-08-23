Import("env")
import os

env.Append(LINKFLAGS=["--coverage"])

# Dummy
print("\n\n\n\n\n\n\n")
env.Execute("pip list")
print("OK\n\n\n\n\n\n\n")

def generateCoverageInfo(source, target, env):
    env.Execute("pip list")    
    env.Execute("echo 2222")
    for file in os.listdir("test"):
        os.system(".pio/build/native/program test/"+file)
    os.system("lcov -d .pio/build/native/ -c -o lcov.info")
    os.system("lcov --remove lcov.info '*/tool-unity/*' '*/test/*' -o filtered_lcov.info")
    os.system("genhtml -o cov/ --demangle-cpp filtered_lcov.info")

env.AddPostAction(".pio/build/native/program", generateCoverageInfo)
