import os
import subprocess
from pathlib import Path

def normalize_lines(content):
    lines = [line.rstrip() for line in content.splitlines()]
    while lines and not lines[-1]:
        lines.pop()
    return lines

def compare_files(c_file, res_file):
    try:
        with open(c_file, 'r') as f1, open(res_file, 'r') as f2:
            c_content = normalize_lines(f1.read())
            res_content = normalize_lines(f2.read())
            return c_content == res_content
    except FileNotFoundError:
        return False
    

def generate_llvmir(sysy_file):
    test_dir = Path("./test/resources/functional")
    if not test_dir.exists():
        return False, "Functional test directory not found."
    
    compiler = Path("./build/compiler")
    if not compiler.exists():
        return False, "compiler not found. Please build the project first."
    
    try:
        base_name = sysy_file.stem
        llvmir_file = test_dir / f"{base_name}.ll"

        subprocess.run(["timeout", "10s", "./build/compiler", sysy_file, llvmir_file])
        return True, "Output generated successfully."
    except Exception as e:
        return False, str(e)
    

def execute_llvmir(llvmir_file):
    test_dir = Path("./test/resources/functional")
    sylib = Path("./test/resources/sylib.c")
    subprocess.run(["clang", llvmir_file, sylib, "-w", "-o", "a.out"])

    base_name = llvmir_file.stem
    input_file = test_dir / f"{base_name}.in"
    output_file = test_dir / f"{base_name}.output"

    if input_file.exists():
        with open(input_file, 'r') as infile, open(output_file, 'w') as outfile:
            result = subprocess.run(
                ["timeout", "60s", "./a.out"],
                stdin=infile,
                stdout=outfile,
            )
    else:
        with open(output_file, 'w') as outfile:
            result = subprocess.run(
                ["timeout", "60s", "./a.out"],
                stdout=outfile,
            )
    with open(output_file, 'r+') as outfile:
        content = outfile.read()
        if content and not content.endswith('\n'):
            outfile.seek(0, 2)
            outfile.write('\n')

    with open(output_file, 'a') as outfile:
        outfile.write(str(result.returncode))
    subprocess.run("rm -f a.out", shell=True)
    return result.returncode

def main():    
    subprocess.run("rm -f ./test/resources/functional/*.ll", shell=True)
    subprocess.run("rm -f ./test/resources/functional/*.output", shell=True)
    
    total_tests = 0
    passed_tests = 0
    results = {}
    
    test_dir = Path("./test/resources/functional")
    
    for sysy_file in sorted(test_dir.glob("*.sy"), key=lambda x: x.name[:2]):

        total_tests += 1
        base_name = sysy_file.stem
        llvmir_file = test_dir / f"{base_name}.ll"
        output_file = test_dir / f"{base_name}.output"
        ans_file = test_dir / f"{base_name}.out"

        success, message = generate_llvmir(sysy_file)
        if not success:
            print(f"[ERROR] {base_name.ljust(14)}: \033[31m✗ LLVMIR Generation Failed\033[0m")  # 红色
            print(f"   {message}")
            continue

        execute_llvmir(llvmir_file)

        if compare_files(ans_file, output_file):
            passed_tests += 1
            results[base_name] = "\033[32m✓ Passed\033[0m"
            print(f"[INFO] {base_name.ljust(14)}: \033[32m✓ Passed\033[0m")  # Green
        else:
            results[base_name] = "\033[31m✗ Failed\033[0m"
            print(f"[ERROR] {base_name.ljust(14)}: \033[31m✗ Failed\033[0m")  # Red

    print("\n╔═══════════════════════════════════════╗")
    print("║            TEST RESULTS               ║")
    print("╠═════════════════════════╦═════════════╣")
    print("║ Test Name               ║ Result      ║")
    print("╠═════════════════════════╬═════════════╣")

    for sysy_file in sorted(test_dir.glob("*.sy"), key=lambda x: x.name[:2]):
        base_name = sysy_file.stem
        print(f"║ {base_name.ljust(23)} ║ {results[base_name]}    ║")

    print("╚═════════════════════════╩═════════════╝")
    print("\n📊 Test Summary:")
    print(f"   Total tests:  {total_tests}")
    print(f"   Passed tests: \033[32m{passed_tests}\033[0m")
    print(f"   Failed tests: \033[31m{total_tests - passed_tests}\033[0m")
    
    if passed_tests == total_tests:
        print("\n\033[32m🎉 All tests passed!\033[0m")
    else:
        print("\n\033[31m⚠️  Some tests failed!\033[0m")

    
if __name__ == "__main__":
    main()