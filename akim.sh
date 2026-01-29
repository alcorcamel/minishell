#!/bin/bash
# Fichier de test pour casser le minishell

# 1️⃣ Commandes inexistantes
no_such_command
lsnonexistent
echoo "typo dans echo"

# 2️⃣ Pipes
ls | | wc
ls | no_such_command
no_such_command | wc

# 3️⃣ Redirections
ls > /non/existing/path/file
cat < /non/existing/file
echo "hello" >> /non/existing/path/file

# 4️⃣ Heredoc edge cases
cat << EOF
Test heredoc normal
EOF

cat << EOF
EOF

cat << EOF
EOF
# ligne vide intentionnelle

# 5️⃣ Commande vide ou espaces
     
# 6️⃣ Combinaisons de pipes et redirections
ls | cat > /non/existing/path/file
ls | no_such_command > /tmp/test.txt
no_such_command | ls > /tmp/test.txt

# 7️⃣ Ctrl-D / EOF tests (tu peux simuler en mettant un fichier vide)
cat < /dev/null
