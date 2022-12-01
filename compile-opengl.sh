src="$1"
if [ -z "$src" ]; then
	echo Error: no input file provided.
	exit 1
fi

filename=$(basename -- "$src")
ext="${filename##*.}"
filename="${filename%.*}"

echo "Compiled $filename.cc -> $filename"
g++ "$src" -lGL -lglut -lGLU -lGLEW -lglfw -o "$filename"
