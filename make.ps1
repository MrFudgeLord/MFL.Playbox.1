Remove-Item a.exe
Remove-Item *.pch -Recurse
clang++ -c *.*pp *.s -masm=intel -O3 -ferror-limit=0 -march=znver5
#clang++ -c *.s *.S -masm=intel -O3
clang++ *.o -o a.exe