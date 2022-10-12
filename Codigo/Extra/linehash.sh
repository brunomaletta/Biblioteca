# Para usar:
# bash linehash.sh arquivo.cpp
while read l; do
	echo $l > tmp.txt
	h=$(echo $(bash hash.sh tmp.txt 1 1) | cut -c-3)
	echo "$h $l"
done < "$1"
