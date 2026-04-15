</div>

<p align='center'>
    <img src="https://capsule-render.vercel.app/api?type=waving&color=4fa69a&height=300&section=header&text=Minishell&fontSize=90&animation=fadeIn&fontAlignY=38&desc=UNIX+shell+built+in+C.&descAlignY=51&descAlign=62"/>

<p align="center">
  <img src="https://img.shields.io/static/v1?label=C&message=Minishell&color=4fa69a&style=for-the-badge&logo=" alt="Project Overview"/>

</p>
</div>

---

<div align="left">

<h3 align="center">Overview</h3>

Minishell is a UNIX shell built in C as part of the 42 curriculum.
It focuses on command parsing, execution pipelines, redirections, environment handling, and shell built-ins.

---

<h3 align="center">Repository Layout</h3>

- `inc/`
- `src/`
- `testee/`

Core logic is organized in dedicated source groups such as parser, tokenizer, AST execution, built-ins, and pipeline handling.

---

<h3 align="center">Build</h3>

From inside the project folder:

```bash
make
```

---

<h3 align="center">Run</h3>

After building, run:

```bash
./minishell
```

---

<h3 align="center">Notes</h3>

- Requires `readline` development libraries available on your system.
- Includes helper targets such as `clean`, `fclean`, `re`, `norm`, and `val`.
- Validate edge cases for quoting, variable expansion, pipes, and redirections.



</div>
