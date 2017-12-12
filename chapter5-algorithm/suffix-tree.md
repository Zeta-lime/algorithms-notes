suffix tree后缀树的构造，ukkonen算法
参考： http://marknelson.us/1996/08/01/suffix-trees/
http://facweb.cs.depaul.edu/mobasher/classes/csc575/Suffix_Trees/index.html
http://blog.163.com/lazy_p/blog/static/13510721620108139476816/
http://www.cnblogs.com/gaochundong/p/suffix_tree.html
https://stackoverflow.com/questions/9452701/ukkonens-suffix-tree-algorithm-in-plain-english
http://www.oschina.net/translate/ukkonens-suffix-tree-algorithm-in-plain-english?lang=chs&page=2#

复杂度O(n)
要点一
path compression 路径压缩
要点二
从左到右逐渐一个一个加入，遍历树中已经存在的suffix（实际上由于路径压缩大多数不用做任何操作）从最长的后缀开始一直到空字符，然后加入这次添加的字符。
rule 1
two types of updates: 
the first was simply the extension of an edge
the second was an implicit update, which involved no work at all. 
要点三
rule 2
the first type, a new node is created to split an existing edge at an implicit node, followed by the addition of a new edge. 在隐含点处分裂并产生新边
The second type of update consists of adding a new edge to an explicit node.
在显式点处添加新边。
重要概念：**active point 活动点**
When updating a suffix tree, the first non-leaf node is defined as the active point of the tree (the first suffix that doesn't terminate at a leaf node). **All of the suffixes** that are **longer** than the suffix defined by the active point will **end in leaf nodes**. None of the suffixes after this point will terminate in leaf nodes.在更新树时，**第一个非叶子节点（后缀从长到短排列，第一个不在叶子处的后缀对应的节点）被定义为活动点**。**比活动点对应后缀长的后缀都对应着叶子节点**，比活动点对应后缀短的都对应着非叶子节点。

算法总结：
1、once a leaf node, always a leaf node. Any node that we creat as a leaf will never be given a descendant, it will only be extend though character concatenation. 
2、we only have to worry about updating explicit and implicit nodes at the active point, which was the first non-leaf node. Given this, we would have to progress from the active point to the empty string, testing each node for update eligibility。
3、As we walk through the suffixes, we will add a new edge to each node that doesn't have a descendant edge starting with the correct character. **When we finally do reach a node that has the correct character as a descendant, we can simply stop updating**. if you find a certain character as a descendant of a particular suffix, you are bound to also find it as a descendant of every smaller suffix.
4、The point where you find the first matching descendant is called **the end point**结束点.we were **adding leaves to every suffix between the active point and the end point, every suffix longer than the end point is a leaf node**.
**在更新后缀树时，后缀从长到短，叶子节点是自动更新不用理会的，加入新的字符，实际上是从“活动点”到“结束点”，活动点对应的后缀之前的后缀的是叶子节点，若活动点无子孙匹配新字符，则在活动点加入新字符的叶子节点，更新活动点（即比当前对应后缀短的前一个后缀对应的节点），直到遇到结束点，结束点之后的后缀（比结束点对应的后缀短）必定都有子孙与新字符匹配，所以意味着结束本轮添加。由于本轮结束时，结束点之前的后缀都变成叶子节点，这意味着下轮时的活动点就是这轮的结束点。**

C-like pseudo code:
```c
Update( new_suffix )
{
  current_suffix = active_point
  test_char = last_char in new_suffix
  done = false;
  while ( !done ) {
    if current_suffix ends at an explicit node {
      if the node has no descendant edge starting with test_char
        create new leaf edge starting at the explicit node
      else
        done = true;
    } else {
      if the implicit node's next char isn't test_char {
        split the edge at the implicit node
        create new leaf edge starting at the split in the edge
      } else
        done = true;
    }
    if current_suffix is the empty string
      done = true;
    else
       current_suffix = next_smaller_suffix( current_suffix )
  }
  active_point = current_suffix
}
```

如何解决`current_suffix = next_smaller_suffix( current_suffix )`
答案是后缀指针suffix pointer
The suffix pointers are built at the same time the update to the tree is taking place.后缀指针在树的更新过程中一起完成。 As I move from the active point to the end point, I keep track of the parent node of each of the new leaves I create. **Each time I create a new edge, I also create a suffix pointer from the parent node of the last leaf edge I created to the current parent edge**.每轮添加新字符（一次update）时，每产生一条叶子节点，则创建一个从该节点的母节点指向上一个创建的新节点的母节点的指针。（第一次创立新节点时则不用这么做。）(Obviously, I can't do this for the first edge created in the update, but I do for all the remaining edges.)