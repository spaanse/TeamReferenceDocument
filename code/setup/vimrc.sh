map <F4> :w <CR> :!~/check.sh % >%.dbg <CR>
	\ :e %.dbg <CR> :bd
map <F5> :w<CR>:!g++ % -o %:r -Wall -g -O3
	\ && echo "compiled"<CR>
map <F6> :!./%:r<CR>
map <F7> :!for f in test/%:r/*.in;
	\ do echo -e "\e[34m$f\e[0m"&&./%:r <$f \|
	\ diff ${f\%.in}.ans -; done <CR>
set ts=4 sts=4 sw=4 noet si hi=1000 rnu ru
