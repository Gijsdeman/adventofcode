import os
import requests
import re

codeRegex = re.compile(r"<pre><code>((.*[\n])*?)</code></pre>")

def fetchExamples(day, inputPath):
    path1 = os.path.join(inputPath, "example.1")
    path2 = os.path.join(inputPath, "example.2")
    if os.path.isfile(path1) and os.path.isfile(path2):
        return

    response = requests.get(url=f"https://adventofcode.com/2023/day/{day}", cookies={
        "session": os.getenv('SESSION')
    })

    examples = codeRegex.findall(response.text)[0][0]
    writeOutput(examples, path1)
    writeOutput(examples, path2)

def fetchInput(day, inputPath):
    path = os.path.join(inputPath, "input")
    if os.path.isfile(path):
        return

    response = requests.get(url=f"https://adventofcode.com/2023/day/{day}/input", cookies={
        "session": os.getenv('SESSION')
    })

    if response.status_code != 200:
        raise Exception("Fetching input failed")

    writeOutput(response.text, path)

def readInput(inputPath):
    return open(inputPath, 'r').read().strip()

def writeOutput(result, outputPath):
    outputFile = open(outputPath, 'w')
    outputFile.write(str(result))
    outputFile.close()