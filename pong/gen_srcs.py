import os

SRC_DIR = "src"
OUT_FILE = "sources.cmake"


def get_sources() -> list:
    return sorted(os.listdir(SRC_DIR))


def gen_cmakefile(sources: list) -> None:
    with open(OUT_FILE, "w") as outfile:
        outfile.write("set(SOURCES\n")
        for source in sources:
            outfile.write(f"\tsrc/{source}\n")
        outfile.write(")\n\n")


if __name__ == "__main__":
    sources = get_sources()
    gen_cmakefile(sources)
