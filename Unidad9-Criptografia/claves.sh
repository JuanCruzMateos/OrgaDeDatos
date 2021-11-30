###########################################################GPG####################################
####   GESTION DE CLAVES

#Genero para de claves
gpg --gen-key

#ver las claves 
gpg --list-keys

##ver las privadas
gpg --list-secret-keys


#exportar clave publica 
gpg --armor --output fichoeDeSalida --exportClaveID 

#exportar clave Privada 
gpg --armor --output fichoeDeSalida --export-secret-key ClaveID
gpg   --export-secret-key -a idclave > private.key.
   
# importar clave
gpg --import ClaveID
gpg --allow-secret-key-import --import private.key
################################## OPERANDO:

###ENCRYPTAR:
 gpg --armor --recipient ClaveID --encrypt  mensaje
###DESENCRYPTAR: 
  gpg --decrypt archivo

FIRMAR 
gpg --clearsign a.txt.

gpg --sign a.txt

VERIFICAR
gpg --verify a.txt.asc 


## ANILLO DE CONFIANZA

 gpg --edit-key id
 comandos:
 trust confianza de la clave
 toggle  
 check   integridad de las claves
 adduid
 deluid  
 addkey
 delkey
 revkey
 expire
 passwd cambia clave de acceso
 save guarda
 

#Ver Huella de la firma (para validar con el otro usuario)
 gpg --fingerprint id
 
 # Firmar una clave publica
 gpg --sign-key id
 
 

# publicar claves publicas en un server
 pgp.rediris.es
  pgp.mit.edu
  
setear  
  gpg --keyserver pgp.rediris.es
enviar
  gpg --send-key uid
recibir
  gpg --recv-keys uid
  
  
 
 
 