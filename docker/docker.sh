echo ========= Build docker image
docker build -t otus.lessons.12.01 .
echo ========= Check matrix version
docker run --rm -i otus.lessons.12.01 matrix -v
echo ========= Execute matrix
docker run --rm -i otus.lessons.12.01 matrix
echo ========= Remove docker image
docker rmi otus.lessons.12.01