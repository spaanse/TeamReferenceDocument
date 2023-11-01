cat $1 | while read -r l; do
h="$(echo -n "$l" | sed 's/\s//g' | md5sum)"
echo "${h:0:2}| $l"; done
