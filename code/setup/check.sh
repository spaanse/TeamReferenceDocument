h="00"; >$2
cat $1 | while IFS= read -r l; do
	s="$(echo "$l" | sed 's/\s//g')"
	nh=$(echo -ne "$s" | md5sum)
	h="0x$h"; nh="0x${nh:0:2}"
	h=$(printf "%02x" "$((h^nh))")
	echo "$h| $l" >> $2
done
