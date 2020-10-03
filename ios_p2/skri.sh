./proj2 1 0 0 0 0
for (( i = 0; i < 100; i++ )); do
	./proj2 50 0 0 0 0
	echo -n "|"
done
echo "done1"
for (( i = 0; i < 100; i++ )); do
	./proj2 50 1000 1 0 1
	echo -n "|"
done
echo "done2"
for (( i = 0; i < 10; i++ )); do
	./proj2 50 2 1000 1 2
	echo -n "|"
done
echo "done3"
for (( i = 0; i < 10; i++ )); do
	./proj2 50 02 01 1200 0
	echo -n "|"
done
echo "done4"
for (( i = 0; i < 10; i++ )); do
	./proj2 50 02 01 1 1200
	echo -n "|"
done
echo "done5"
for (( i = 0; i < 10; i++ )); do
	./proj2 50 2000 2000 2000 2000
	echo -n "|"
done
echo "frajer"
