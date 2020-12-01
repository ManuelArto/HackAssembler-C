import os

os.system("make -C src")

files = ["Add.asm", "MaxL.asm", "PongL.asm",  "RectL.asm", "Max.asm", "Rect.asm", "Pong.asm"]

for file in files:
	os.system(f"./src/assembler ./{file}")

for file in files:
	print(f"Diff {file.replace('.asm', '.hack')} {file.replace('.asm', 'Correct.hack')}")
	os.system(f"diff {file.replace('.asm', '.hack')} {file.replace('.asm', 'Correct.hack')}")
	print()
