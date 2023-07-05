
# @doc README.md
# ## Examples
# 
# See the following files for examples:
# 
# - `./doc/make_readme.sh`: A simple shell script which compiles a tiny c++
#   programme that in turn makes `README.md`.

if [ -d ./tmp/ ]; then
    rm -rf ./tmp/
fi
mkdir ./tmp/
echo "<!-- generated by ./doc/make_readme.sh; do not edit manually -->" > ./tmp/README.md
g++ ./doc/make_readme.cpp -I./ -o ./tmp_exe
./tmp_exe
rm ./tmp_exe
cp -f ./tmp/README.md ./README.md
rm -rf ./tmp/
