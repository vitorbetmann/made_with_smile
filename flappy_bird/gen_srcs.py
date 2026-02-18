import os
from typing import TextIO

SRC_DIR = "src"
OUT_FILE = "sources.cmake"


def get_sources(source) -> list[str]:
    return os.listdir(source)


def gen_cmakefile(sources: list[str], srcdir: str, file: TextIO) -> None:
    for source in sources:
        if source.endswith(".c"):
            file.write(f"\t{srcdir}/{source}\n")
            continue

        new_dir = f"{srcdir}/{source}"
        if os.path.isdir(new_dir):
            new_dir_srcs = get_sources(new_dir)
            gen_cmakefile(new_dir_srcs, new_dir, file)


if __name__ == "__main__":
    sources = get_sources(SRC_DIR)

    with open(OUT_FILE, "w") as outfile:
        outfile.write("set(SOURCES\n")
        gen_cmakefile(sources, SRC_DIR, outfile)
        outfile.write(")\n\n")
