#Remove-Item a.exe
#Remove-Item *.pch -Recurse
# clang++ MFL.* -masm=intel -O3 -ferror-limit=0 -march=znver5 -o a.exe
clang++ -ferror-limit=0 -masm=intel -march=znver5 -o playbox.exe -I include -l SDL3.dll