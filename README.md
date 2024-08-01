# 前言
C++练手项目，用于Linux环境下的Socket接收与发送

# Roadmap
- 作为服务端，接收数据
- 作为客户端，发送数据
- 实现单个连接、多个连接与多路IO复用：select与epoll
- 实现字符串与文件的接收/发送
- 实现自动化测试
- 实现函数性能分析
- 实现服务端，与CI自动化部署

# 提交信息规范说明

在本项目中，我们使用一套标准化的提交信息格式来确保提交记录的清晰性和一致性。请遵循以下规范进行提交：

## 基本格式

提交信息的基本格式如下：

```
<type>: <subject>

<description>
```

- **`<type>`**: 提交类型，表示此次更改的类别。具体类型如下：
    - **`feat`**: 新功能的引入
    - **`fix`**: 错误修复
    - **`docs`**: 文档相关的变更
    - **`style`**: 代码风格的更改（不影响代码含义的变动，例如空白、格式化等）
    - **`refactor`**: 代码重构（既不是新功能也不是修复 bug 的代码变动）
    - **`test`**: 添加或修改测试
    - **`chore`**: 不修改源代码或测试文件的其他更改（如构建过程或辅助工具的更改）
    - **`revert`**: 撤销某次提交

- **`<subject>`**: 简要描述此次更改的内容。应简洁明了，通常控制在50个字符以内。

- **`<description>`**: 可选的详细描述，用于解释更改的动机和背景。描述部分应放在第一行空行之后，可以包含多行内容。

## 提交信息示例

1. **简单提交信息（无详细描述）**

   ```
   feat: Add image upload functionality
   ```

2. **复杂提交信息（带详细描述）**

   ```
   fix: Correct image upload error
   
   Fixed an issue where images were not being correctly uploaded to the server
   due to a missing content-type header. Updated the upload logic to ensure
   proper MIME type handling.
   ```