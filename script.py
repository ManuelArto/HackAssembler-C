import os

# compile
os.system("make -C src")

files = ["Add.asm", "MaxL.asm", "PongL.asm",  "RectL.asm", "Max.asm", "Rect.asm", "Pong.asm"]

# exec
for file in files:
	os.system(f"./src/assembler ./{file}")

# checking
for file in files:
	print(f"Checking {file.replace('asm', 'hack')} {file.replace('asm', 'Correcthack')}")

	hackfile = open(file.replace('asm', 'hack'), 'r')
	hack_correctfile = open(file.replace('.asm', 'Correct.hack'), 'r')

	line_count = 1
	for hackline, hack_correctline in zip(hackfile.readlines(), hack_correctfile.readlines()):
		if hackline != hack_correctline:
			print(f"ERROR at line {line_count}:")
			print(f"\t{hackline.strip()} had to be {hack_correctline.strip()}")
		line_count += 1
	else:
		print("Correct\n")

	hack_correctfile.close()
	hackfile.close()
