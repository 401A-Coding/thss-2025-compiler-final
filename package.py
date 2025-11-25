import os
import zipfile

def zip_directory(zipf, directory):
    for root, _, files in os.walk(directory):
        for file in files:
            file_path = os.path.join(root, file)
            zipf.write(file_path)

def main():
    # Check if all required files are present
    if not (os.path.isdir("src") and os.path.isfile("CMakeLists.txt")):
        print("Error: Missing src directory or CMakeLists.txt file")
        return
    if not os.path.isdir("include"):
        print("Error: Missing include directory")
        return
    if not os.path.isfile("SysYLexer.g4"):
        print("Error: Missing SysYLexer.g4 file")
        return
    if not os.path.isfile("SysYParser.g4"):
        print("Error: Missing SysYParser.g4 file")
        return
    
    # Create the zip archive
    with zipfile.ZipFile("project.zip", "w", zipfile.ZIP_DEFLATED) as zipf:
        zip_directory(zipf, "src")
        zip_directory(zipf, "include")
        zipf.write("CMakeLists.txt")
        zipf.write("SysYLexer.g4")
        zipf.write("SysYParser.g4")
        
    print("Zip archive created: project.zip")

if __name__ == "__main__":
    main()