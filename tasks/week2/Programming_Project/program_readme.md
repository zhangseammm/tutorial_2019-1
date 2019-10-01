#程序练习题 链表加法

##算法思路

这是一道比较简单的题。由于链表本身放的数字是逆序的，所以链表头就是最低位。所以要做加法的话只需要不断地沿着链表做加法即可。唯一要考虑的就是链表可能会有进位，那么由此会引发一系列要考虑的问题：比如说连续进位，或者是最后的加法多了一位，这些都已经考虑到了。

##注意事项

- 由于本人上次程序题是0分，所以这次题目在leetcode上进行了测试并成功通过。所以如果师兄测试出现错误麻烦私聊一下我！QQ号码：454012054.

- 根据要求，只提交了一个函数的cpp