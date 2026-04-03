# Comandos Git

listar branchs locais:
```
git branch
```
--- 

listar todas as branchs:
```
git branch -a
```
_obs: lista as branchs locais e as remotas_

---

criar branch:
```
git checkout -b nome-da-branch
```
_obs: cria a branch a partir da branch atual_

---

deletar branch:
```
git branch -d nome-da-branch
```
_obs: só é possível deletar a branch estando fora dela_

---

stage todas as mudanças
```
git add .
```

---

commit todas as mudanças que estão staged
```
git commit -m"mensagem do commit"
```

---

enviar mudanças para o repositório remoto (github)
```
git push
```

---

puxar as mudanças do repositório remoto
```
git pull
```
_obs: sempre bom dar esse comando antes se tiver alguém mexendo na sua branch tambpem_

---

dar merge da branch na master 
```
git checkout master
git merge nome-da-branchs
```
_obs: quando terminou sua atividade e quer mandar para a master_

---

dar merge da master na branch da atividade 
```
git checkout sua-branch
git merge master
```

_obs: quando quer atualizar a sua branch de atividade com a master atual_

---