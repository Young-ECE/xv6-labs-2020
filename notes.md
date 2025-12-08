# Git 常用命令笔记

## 远程仓库管理

### 查看远程仓库
```bash
# 查看所有远程仓库
git remote -v

# 查看远程仓库详细信息
git remote show origin
git remote show young-github
```

### 添加/修改远程仓库
```bash
# 添加新的远程仓库
git remote add <名称> <URL>
# 例如：git remote add young-github https://github.com/Young-ECE/xv6-labs-2020.git

# 修改现有远程仓库的 URL
git remote set-url <名称> <新URL>
# 例如：git remote set-url origin https://github.com/Young-ECE/xv6-labs-2020.git

# 删除远程仓库
git remote remove <名称>
```

## 分支管理

### 查看分支
```bash
# 查看本地分支
git branch

# 查看所有分支（包括远程）
git branch -a

# 查看分支详细信息（包括上游分支）
git branch -vv

# 查看远程分支
git branch -r
```

### 创建和切换分支
```bash
# 创建新分支
git branch <分支名>

# 创建并切换到新分支
git checkout -b <分支名>

# 从远程分支创建本地分支
git checkout -b <本地分支名> <远程仓库>/<远程分支名>
# 例如：git checkout -b util origin/util

# 切换到已有分支
git checkout <分支名>

# 切换到 main 分支
git checkout main
```

### 设置分支上游
```bash
# 设置当前分支的上游分支
git branch --set-upstream-to=<远程仓库>/<分支名> <本地分支名>
# 例如：git branch --set-upstream-to=young-github/util util

# 在推送时设置上游（推荐）
git push -u <远程仓库> <分支名>
# 例如：git push -u young-github util
```

### 删除分支
```bash
# 删除本地分支
git branch -d <分支名>        # 安全删除（已合并）
git branch -D <分支名>        # 强制删除（未合并）

# 删除远程分支
git push <远程仓库> --delete <分支名>
# 例如：git push young-github --delete old-branch
```

## 获取和同步代码

### 获取远程代码
```bash
# 获取所有远程仓库的最新信息（不合并）
git fetch

# 获取特定远程仓库的信息
git fetch origin
git fetch young-github

# 获取并合并远程分支
git pull

# 获取特定远程分支并合并
git pull origin master
```

### 推送代码
```bash
# 推送到上游分支（如果已设置）
git push

# 推送到指定远程仓库和分支
git push <远程仓库> <分支名>
# 例如：git push young-github main

# 推送并设置上游
git push -u <远程仓库> <分支名>

# 推送所有分支
git push <远程仓库> --all

# 推送所有标签
git push <远程仓库> --tags
```

## 提交管理

### 查看状态和日志
```bash
# 查看工作区状态
git status

# 查看提交历史
git log

# 查看简洁的提交历史
git log --oneline

# 查看图形化的提交历史
git log --graph --oneline --all

# 查看文件差异
git diff                    # 工作区与暂存区的差异
git diff --staged           # 暂存区与最后一次提交的差异
git diff HEAD               # 工作区与最后一次提交的差异
```

### 添加和提交
```bash
# 添加文件到暂存区
git add <文件名>            # 添加单个文件
git add .                   # 添加所有修改的文件
git add -A                  # 添加所有文件（包括删除的）

# 提交更改
git commit -m "提交信息"

# 添加并提交（跳过暂存区）
git commit -am "提交信息"
```

### 修改提交
```bash
# 修改最后一次提交信息
git commit --amend -m "新的提交信息"

# 修改最后一次提交（添加遗漏的文件）
git add <遗漏的文件>
git commit --amend --no-edit
```

## 撤销操作

### 撤销工作区修改
```bash
# 撤销工作区的修改（危险！）
git checkout -- <文件名>
git restore <文件名>        # Git 2.23+ 新命令

# 撤销所有工作区修改
git checkout -- .
git restore .               # Git 2.23+ 新命令
```

### 撤销暂存区
```bash
# 将文件从暂存区移除（保留工作区修改）
git reset HEAD <文件名>
git restore --staged <文件名>  # Git 2.23+ 新命令
```

### 撤销提交
```bash
# 撤销最后一次提交（保留修改在暂存区）
git reset --soft HEAD~1

# 撤销最后一次提交（保留修改在工作区）
git reset --mixed HEAD~1
git reset HEAD~1            # 默认是 mixed

# 撤销最后一次提交（完全删除修改）
git reset --hard HEAD~1     # 危险！会丢失所有修改
```

## 合并和变基

### 合并分支
```bash
# 合并分支到当前分支
git merge <分支名>

# 合并时创建合并提交
git merge --no-ff <分支名>
```

### 变基
```bash
# 将当前分支变基到目标分支
git rebase <目标分支>

# 交互式变基（可以修改提交历史）
git rebase -i HEAD~3        # 修改最近3个提交
```

## 标签管理

### 创建标签
```bash
# 创建轻量标签
git tag <标签名>

# 创建附注标签
git tag -a <标签名> -m "标签说明"

# 在特定提交上创建标签
git tag <标签名> <提交哈希>
```

### 查看和推送标签
```bash
# 查看所有标签
git tag

# 查看标签信息
git show <标签名>

# 推送标签到远程
git push <远程仓库> <标签名>
git push <远程仓库> --tags  # 推送所有标签
```

## MIT 6.S081 项目特定工作流

### 开始新实验
```bash
# 1. 获取最新的远程分支信息
git fetch origin

# 2. 从远程实验分支创建本地分支
git checkout -b <实验名> origin/<实验名>
# 例如：git checkout -b util origin/util

# 3. 设置上游并推送到自己的仓库
git push -u young-github <实验名>
```

### 完成实验过程中的操作
```bash
# 查看当前状态
git status

# 添加修改
git add .

# 提交
git commit -m "完成实验的 xxx 部分"

# 推送到自己的 GitHub
git push
```

### 完成实验后
```bash
# 最终提交
git add .
git commit -m "完成 <实验名> 实验"

# 推送到 GitHub
git push

# （可选）合并到 main 分支
git checkout main
git merge <实验名>
git push young-github main
```

## 常用组合命令

### 查看当前分支的上游设置
```bash
git branch -vv
```

### 查看所有远程分支的详细信息
```bash
git remote show origin
git remote show young-github
```

### 清理未跟踪的文件
```bash
# 查看哪些文件会被删除
git clean -n

# 删除未跟踪的文件
git clean -f

# 删除未跟踪的文件和目录
git clean -fd
```

### 查看特定文件的提交历史
```bash
git log <文件名>
git log --follow <文件名>  # 跟踪文件重命名
```

## 配置相关

### 查看配置
```bash
# 查看所有配置
git config --list

# 查看特定配置
git config user.name
git config user.email
```

### 设置配置
```bash
# 设置用户名和邮箱（全局）
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"

# 设置用户名和邮箱（仅当前仓库）
git config user.name "Your Name"
git config user.email "your.email@example.com"
```

## 实用技巧

### 查看某个提交的详细信息
```bash
git show <提交哈希>
```

### 查看某个文件在某个提交时的内容
```bash
git show <提交哈希>:<文件路径>
```

### 比较两个分支的差异
```bash
git diff <分支1> <分支2>
```

### 查看某个提交修改了哪些文件
```bash
git show --name-only <提交哈希>
git show --stat <提交哈希>
```

### 暂存当前修改（临时切换分支）
```bash
# 暂存修改
git stash

# 查看暂存列表
git stash list

# 恢复暂存
git stash pop              # 恢复并删除
git stash apply            # 恢复但保留

# 删除暂存
git stash drop
```

---

## 注意事项

1. **推送前先拉取**：在推送前最好先 `git pull` 或 `git fetch` 确保本地是最新的
2. **提交信息要清晰**：使用有意义的提交信息，方便后续查看历史
3. **重要操作前备份**：在执行 `git reset --hard` 等危险操作前，确保重要代码已提交或备份
4. **定期推送**：完成阶段性工作后及时推送到远程仓库，避免本地丢失
5. **分支命名规范**：使用清晰的分支名，如 `util`、`syscall` 等实验名称

