# Proxy (pt-br)
  Alterando o proxy pelos registros do Windows utilizando a windowsAPI.

#🔨Compilando
  -Estou utilizando o Code Blocks mas você pode fazer por outra IDE.
  -Abra o projeto na IDE (main.cpp)
  -Compile o script (no caso do Code Blocks pressione o atalho F9)
  -Após compilar entre no diretório do seu projeto e abra o arquivo .exe que foi gerado

#🤓Testando
  -Vamos utilizar dois comandos no CMD para verificar o valor das chaves ProxyServer e ProxyPort
  -Digite os codigos no cmd e pressione ENTER:
  
    reg query "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings" /v ProxyServer
    
    reg query "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings" /v ProxyPort
    
  -Os comandos irão retornar uma mensagem como essa(os asteriscos serão o valor proxy do script): 
  
    HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings
      ProxyServer    REG_SZ    ***************
      
  # Proxy (en)
  Change proxy through windows registries using windowsAPI.

# 🔨Compiling
  -I'm using Code Blocks, but you can use another IDE.
  -Open the project in the IDE (main.cpp)
  -Compile the script (in the case of Code Blocks press the shortcut F9)
  -After compilation, enter your project directory and open the .exe file that was generated

# 🤓Test
  -Let's use two commands in CMD to check value of ProxyServer and ProxyPort keys
  -Type the codes in cmd and press ENTER:
  
    1: reg query "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings" /v ProxyServer
    2: reg query "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings" /v ProxyPort
    
  -The commands will return a message like this (the asterisks will be the proxy value of the script):
  
    HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings
      ProxyServer REG_SZ ***************
