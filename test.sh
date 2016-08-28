#!/bin/bash
# test script for 'x'

function sha1 {
	sha1sum | awk '{ print $1 }'
}

function test_x {
	flags=$1
	answer=$2
	result=$(cat testfile | ./x $flags | sha1)

	if [[ $result = $answer ]]; then
		printf -- "\033[38;5;040m[\$]\033[m passed! flags: %s\n" "$flags"
	else
		printf -- "\033[38;5;196m[\$]\033[m FAILED! flags: %s\n" "$flags"
		printf -- "\texpected: %s\n" "$answer"
		printf -- "\t     got: %s\n" "$result"
	fi
}



testfile_sum=$(cat testfile | sha1)
if [[ ! $testfile_sum = '7315b14ca01a9d8638d417a04f845daa55a9d008' ]]
then
	printf -- "the testfile is missing or wrong or something" >&2
	exit 1
fi

test_x ''    '93c61198cbbc24fe467debd3081225ea751c6553'
test_x '-a'  'acd8df131c6cafb62947d7f2d8baed427c269dd9'
test_x '-t'  '0ae6a07134ea37a85f464202c3153dd9d8b2425b'
test_x '-n'  '77544e0f487ab1334599f5370c5dfdd216615540'
test_x '-r'  '5a76bd40774d59ef08275c6f96b87efd8c57ed02'
test_x '-s'  'ecf67c95653dee5aa49ffb5805aa0a3c380d148d'
test_x '-i'  'bd58bcf05e6a66d0a02b00e16f1e3ce45e3f5eae'
test_x '-u'  '455cc06ebaaa933cd38cc6a153006157e309c175'
test_x '-aa' 'acd8df131c6cafb62947d7f2d8baed427c269dd9'
test_x '-at' 'acd8df131c6cafb62947d7f2d8baed427c269dd9'
test_x '-ar' 'acd8df131c6cafb62947d7f2d8baed427c269dd9'
test_x '-as' 'acd8df131c6cafb62947d7f2d8baed427c269dd9'
test_x '-an' 'acd8df131c6cafb62947d7f2d8baed427c269dd9'
test_x '-ai' 'acd8df131c6cafb62947d7f2d8baed427c269dd9'
test_x '-ta' 'acd8df131c6cafb62947d7f2d8baed427c269dd9'
test_x '-tt' '0ae6a07134ea37a85f464202c3153dd9d8b2425b'
test_x '-au' 'ff506cd2c2ed02faf5abf66a550a79ff912fe0df'
test_x '-tn' 'b76972106d17f95cb4352a9966aef592e239f8ed'
test_x '-tr' 'be11d265e42c970e8fc58e24bd22ab62680c5c99'
test_x '-ti' 'a100404bac82ddce564e4cf2d6e1d17c0afd121f'
test_x '-ts' '096fe8b03cc75373d8a1bea5a3480acc65beb247'
test_x '-na' 'acd8df131c6cafb62947d7f2d8baed427c269dd9'
test_x '-nt' 'b76972106d17f95cb4352a9966aef592e239f8ed'
test_x '-nn' '77544e0f487ab1334599f5370c5dfdd216615540'
test_x '-tu' '5a5dd6239218f6d63bcfbf76fdb82861db064b99'
test_x '-ns' '059c30e8b7bee681956eb7666c5abecab055e861'
test_x '-ni' '580059c9c7b543073d1867072457e2ba7e2d114f'
test_x '-nu' 'b60d904e8dacfc73687f78179b9276c1e0a16937'
test_x '-nr' '14b66df9df8b773105d89d8975af8347d05ec39e'
test_x '-ra' 'acd8df131c6cafb62947d7f2d8baed427c269dd9'
test_x '-rn' '14b66df9df8b773105d89d8975af8347d05ec39e'
test_x '-rt' 'be11d265e42c970e8fc58e24bd22ab62680c5c99'
test_x '-rr' '5a76bd40774d59ef08275c6f96b87efd8c57ed02'
test_x '-rs' '8f5f6cbc04c3034c09b61ad5dfdd1dd446d451a1'
test_x '-ru' 'e6271d1a0d2c3779966823641db7b8b3367b158f'
test_x '-sa' 'acd8df131c6cafb62947d7f2d8baed427c269dd9'
test_x '-st' '096fe8b03cc75373d8a1bea5a3480acc65beb247'
test_x '-sn' '059c30e8b7bee681956eb7666c5abecab055e861'
test_x '-sr' '8f5f6cbc04c3034c09b61ad5dfdd1dd446d451a1'
test_x '-ri' '2e005434cf8a1e9243de67251f7a1886171bc1ea'
test_x '-si' 'ef09d749cb668981d5503e98d68e8d3e33018116'
test_x '-su' 'c01bb3db446df945e07ac4d2c56c05e1201d99b5'
test_x '-ss' 'ecf67c95653dee5aa49ffb5805aa0a3c380d148d'
test_x '-ia' 'acd8df131c6cafb62947d7f2d8baed427c269dd9'
test_x '-in' '580059c9c7b543073d1867072457e2ba7e2d114f'
test_x '-it' 'a100404bac82ddce564e4cf2d6e1d17c0afd121f'
test_x '-ir' '2e005434cf8a1e9243de67251f7a1886171bc1ea'
test_x '-is' 'ef09d749cb668981d5503e98d68e8d3e33018116'
test_x '-iu' 'fe12ce022ddd37400253062aa842cb3448b1ee95'
test_x '-ua' 'ff506cd2c2ed02faf5abf66a550a79ff912fe0df'
test_x '-ii' 'bd58bcf05e6a66d0a02b00e16f1e3ce45e3f5eae'
test_x '-ut' '5a5dd6239218f6d63bcfbf76fdb82861db064b99'
test_x '-ur' 'e6271d1a0d2c3779966823641db7b8b3367b158f'
test_x '-un' 'b60d904e8dacfc73687f78179b9276c1e0a16937'
test_x '-us' 'c01bb3db446df945e07ac4d2c56c05e1201d99b5'
test_x '-ui' 'fe12ce022ddd37400253062aa842cb3448b1ee95'
test_x '-uu' '455cc06ebaaa933cd38cc6a153006157e309c175'


