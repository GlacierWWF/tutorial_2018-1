# git的工作流
git是分布式版本控制系统。
![WorkFlow]()
- 各分支的介绍：
  - 常用分支
    - master是主分支，仅用于发布成熟的重大版本。
    - Develop用于日常开发。
  - 临时分支
   > 这些分支需要及时用`git branch -d <branch_name>`删除
    - feature功能分支专注实现某项具体功能，围绕Develop进行。
    - release预发布分支，当Develop已具有足够功能后便开此分支为发布做准备，之后的新功能不再添至此，仅进行Debug后合并入master
    - fixbug修补bug分支。
- 分支的操作
  - 创建分支并进入：`git checkout -b <new_branch> <parent_branch>`
  - 切换分支:`git checkout <branch>`
  - 合并分支：默认是FastForword方式，直接改变分支指针指向，不建议。建议使用`git merge --no--off <branch_name>`打开文件解决冲突即可。

