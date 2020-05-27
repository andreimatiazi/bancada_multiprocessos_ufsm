## Sistema para aquisição de dados de bancada multiprocessos localizada na UFSM

- No projeto foi realizado um sistema de monitoramento local e remoto utilizando arduino e um módulo ethernet  utilizando o protocolo TCP/IP para a conexão com o controlador da planta. 

```sh
  - Na configuração local foi utilizada um arduino mega comunicando via conexão serial com um notebook rodando um servidor local construido em python, os dados são posteriormente enviados ao Firebase.

  - Na configuração remota foi construido um aplicativo e React Native consumindo os dados armazenados no Firebase.
```