一階層：
9, 2, 21, 15, 20, 3, 7, 1, 6, 11, 17, 4, 19, 16, 10, 13, 18, 5, 12, 22, 8, 14

再帰：
①size: 1
※一個のpairにbigとsmallの距離が1となる、bigとsmallはそれぞれ1個要素が入っている

②下記のiterator listを作る
big:   9, 21, 20, 7, 11, 17, 19, 13, 18, 22, 14
small: 2, 15, 3,  1, 6,  4,  16, 10, 5,  12, 8

return:
①small → bigの順に要素をtemp＿sorted_listに格納する（最後にlist_の値へ書き換える）
※returnが帰る前に順番が書き換えるので、同じiteratorでも中は違う値が入っている

big:   7, 9, 11, 13, 17, 18, 19, 20, 21, 22, 14
small: 1, 2, 6,  10, 4,  5,  16, 3,  15, 12, 8

temp_sorted_list:
1 → 7 → 9 → 11 → 13 → 17 → 18 → 19 → 20 → 21 → 22 → 14

②jacobsthal_numberを作る→numberでsmall_listをグループ分けし、
　　　　numberを後ろから切り出してからbinary-insertを行う


③binary-insert(temp_sorted_list, size, insert_it)

2,6 → 1, 7, 9

10,4 → 1, 2, 6, 7, 9, 11, 13

5,16,3,15,12,8  → 1, 2, 4, 6, 7, 9, 10, 11, 13

temp_sorted_list:
1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → 10 → 11 → 13 → 14 → 15 → 16 → 17 → 18 → 19 → 20 → 21 → 22

④list_をtemp_sorted_listで書き換える
list_の順番は下記になる
1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 ,14, 15, 16, 17, 18, 19, 20, 21, 22

---------------------------------------------------------------------------------------------

二階層：
9, 21, 20, 7, 11, 17, 19, 13, 18, 22, 14
2, 15, 3,  1, 6,  4,  16, 10, 5,  12, 8

再帰：
①size: 2
※一個のpairにbigとsmallの距離が2となる、bigとsmallはそれぞれ2個要素が入っている

②下記のiterator listを作る
big:   21, 20, 17, 19, 22
small: 9,  7,  11, 13, 18, 14

return
①small → bigの順に要素をtemp＿sorted_listに格納する（最後にlist_の値へ書き換える）
※returnが帰る前に順番が書き換えるので、同じiteratorでも中は違う値が入っている

big:   17, 19, 20, 21, 22
small: 11, 13, 7,  9,  18, 14

temp_sorted_list:
11, 6 → 17, 4 → 19, 16 → 20, 3 → 21, 15 → 22, 8

②jacobsthal_numberを作る→numberでsmall_listをグループ分けし、
　　　　numberを後ろから切り出してからbinary-insertを行う

③binary-insert(temp_sorted_list, size, insert_it)
7  →　11, 17, 19にbinary-insert
13 →  7,  11, 17, 19にbinary-insert

18 →　7, 11, 13, 17, 19, 20, 21
9  →　7, 11, 13, 17, 18, 19, 20, 21

14 →　7, 9, 11, 13, 17, 18, 19, 20, 21

temp_sorted_list：
7,1 → 9,2 → 11,6 → 13,10 → 14,8 → 17,4 → 14,8 → 18,5 → 19,16 → 20,3 → 21,15 → 22,12

※一回size分を飛ばして、size分をinsertする

④list_をtemp_sorted_listで書き換える
temp_sorted_list:
↓
list_をtemp_sortedに書き換える
↓
list_の順番は下記になる
7, 9, 11, 13, 14 17, 18, 19, 20, 21, 22
1, 2, 6,  10, 8  4,  5,  16, 3,  15, 12

---------------------------------------------------------------------------------------------

三階層：
b , s,  b,  s,  b,  s
21, 20, 17, 19, 22
15, 3,  4,  16, 12

9,  7,  11, 13, 18, 14
2,  1,  6,  10, 5,  8

再帰：
①size: 4
※一個のpairにbigとsmallの距離が4となる、bigとsmallはそれぞれ4個要素が入っている

②下記のiterator listを作る
big:   21, 19
small: 20, 17, 22

return:
①small → bigの順に要素をtemp＿sorted_listに格納する（最後にlist_の値へ書き換える）
※returnが帰る前に順番が書き換えるので、同じiteratorでも中は違う値が入っている

big:   19, 21
small: 17, 20, 22

temp_sorted_list:
17, 4, 11, 6 → 19, 16, 13, 10 →  21, 15, 9, 2

②jacobsthal_numberを作る→numberでsmall_listをグループ分けし、
　　　　numberを後ろから切り出してからbinary-insertを行う

・jacobsthal_numberを作られた
・small_itをどのように移動する？
 while文で制御、一回のループにbinary-insertの探す対象に調整


③binary-insert(temp_sorted_list, small_it, size)

・temp_sorted_list　→　it_listを作成（insert先を作成する）
・binary-search(it_list, item(探す対象：small_it), begin(0), end(count_index)：itが返されて、どこにinsertするかわかる
 ※make a func to count pair index



・insert(it（どこ）,size（何個）)：どこにsmall_itから何個の要素を入れる関数

22　→　17,19,21にbinary-insert
20　→　17,19,21,22にbinary-insert

temp_sorted_list:
17, 4, 11, 6 →　19, 16, 13, 10 → 20, 3, 7, 1 →　21, 15, 9, 2 → 22, 8, 18, 5

※一回size分を飛ばして、size分をinsertする

④list_をtemp_sorted_listで書き換える
temp_sorted_list:
↓
list_をtemp_sortedに書き換える
↓
list_の順番は下記になる
17, 19, 20, 21, 22
4,  16, 3,  15, 8

11, 13, 7,  9,  18
6,  10, 1,  2,  5

---------------------------------------------------------------------------------------------

四階層：
b,  s , b
21, 19,
15, 16,
9,  13,
2,  10,

20, 17, 22
3,  4,  12
7,  11, 18
1,  6,  5

再帰：
①size: 8
※一個のpairにbigとsmallの距離が8となる、bigとsmallはそれぞれ8個要素が入っている

②下記のiterator listを作る
big:   21
small: 19

return:
①small → bigの順に要素を新しいtemp_sorted_listにinsert

big:   21
small: 19

temp_sorted_list:
19, 16, 13, 10, 17, 4, 11, 6 → 21, 15, 9, 2, 20, 3, 7, 1
↓
list_をtemp_sortedで書き換える
↓
list_の順番は下記になる
19, 21
16, 15
13, 9
10, 2

17, 20, 22
4,  3,  12
11, 7,  18
6,  1,  5

②smallに残ったiteratorの値をsorted_listに格納したnumberにバイナリーインサートする
※smallがなくなったのでやらない

③list_をtemp_sorted_listで書き換える
temp_sorted_list:
19, 16, 13, 10, 17, 4, 11, 6 → 21, 15, 9, 2, 20, 3, 7, 1
↓
list_をtemp_sortedに書き換える
↓
list_の順番は下記になる
19, 21
16, 15
13, 9
10, 2

17, 20, 22
4,  3,  12
11, 7,  18
6,  1,  5

--------------------------------------------------------------------------------------------

五階層:
21
15
9
2
20
3
7
1

19
16
13
10
17
4
11
6

再帰：
①size: 16
※一個のpairにbigとsmallの距離が16となる、bigとsmallはそれぞれ16個要素が入っている
　→一個pairを整列するためのnumber数が足りないので、returnする


---------------------------------------------------------------------------------------------


9 2 21 15 20 3 7 1 6 11 17 4 19 16 10 13 18 5 12 22 8 14