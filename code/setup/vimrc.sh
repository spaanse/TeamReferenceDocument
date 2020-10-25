map <F4> :w <CR> :!~/check.sh % %.dbg <CR>
	\ :e %.dbg <CR> :bd
map <F5> :w<CR>:!g++ % -o %:r -Wall -g -O3
	\ && echo "compiled"<CR><CR>
map <F6> :!./%:r<CR>
set ts=4 sts=4 sw=4 noet si hi=1000 rnu ru
