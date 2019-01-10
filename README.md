# Source - Contest

这个分支记录了大部分我曾经参加过的考试（订正）源代码

## 一个惨案
```diff
30c30
<       return list.reduce((p, c) => (p || c.test(str)), false)
---
>       return list.reduce((p, c) => (p && c.test(str)), false)
```
