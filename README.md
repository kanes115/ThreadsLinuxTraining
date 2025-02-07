# ThreadsLinuxTraining
This is a little training to get used to threads in linux.

## Exercise

### Zadanie 1
Napisz program przyjmujący cztery argumenty: ilość wątków, nazwę pliku, ilość rekordów czytanych przez wątek w pojedynczym odczycie i słowo do wyszukania w rekordzie. Plik zawiera rekordy o stałym rozmiarze 1024 bajtów. Rekord składa się z pola id (int) oraz z pola text (pozostały rozmiar rekordu). Program otwiera plik przekazany w argumencie, po czym tworzy zadaną ilość wątków. Wątki czytają naprzemiennie funkcją read ustalone ilości rekordów z otwartego pliku. Wątki powinny przechowywać czytane rekordy pliku w swoich danych własnych. W polach text rekordów wątki poszukują słowa przekazanego przez parametr. Po odszukaniu zadanego słowa wątek powinien wypisać na ekran swój identyfikator (TID) i id rekordu.

Stwórz trzy wersje programu. W wersji pierwszej, po odszukaniu słowa wątek anuluje asynchronicznie wszystkie pozostałe wątki i kończy pracę. W wersji drugiej wątek, który odszukał napis również anuluje pozostałe wątki, lecz anulowanie jest synchroniczne - punktem anulowania wątku jest zakończenie przetwarzania wczytanej ilości rekordów do danych prywatnych. W wersji trzeciej wszystkie wątki powinny być odłączone a warunkiem zakończenia wątku jest odczytanie wszystkich rekordów pliku.

### Zadanie 2
a) Przeprowadź testy dotyczące zachowania się wątków w reakcji na nadchodzące sygnały. Uwzględnij następujące sygnały: SIGUSR1, SIGTERM, SIGKILL, SIGSTOP. Poddaj odpowiednim modyfikacjom program użyty w Zadaniu 1.

Wyślij te sygnały do całego procesu (kill) oraz do poszczególnych wątków (kill/pthread_kill). Opisz w pliku „zad2.raport” rezultaty poniższych działań, biorąc pod uwagę, które watki zostały zatrzymane lub zabite i jakie komunikaty zostały wypisane. Odrzuć te działania, które ze względu na właściwości poszczególnych sygnałów są niemożliwe do wykonania. 
Oto operacje do przetestowania wyników:

wysłanie sygnału do procesu, gdy żaden wątek nie ma zamaskowanego tego sygnału
wysłanie sygnału do procesu, gdy główny wątek programu ma zamaskowany ten sygnał, a wszystkie pozostałe wątki nie,
wysłanie sygnału do procesu, gdy wszystkie wątki mają zainstalowaną niestandardową procedurę obsługi przerwania, która wypisuje informację o nadejściu tego sygnału oraz PID i TID danego wątku
wysłanie sygnału do wątku z zamaskowanym tym sygnałem
wysłanie sygnału do wątku, w którym zmieniona jest procedura obsługi sygnału, jak przedstawiono w punkcie 3
Zaznacz, jeśli są jakieś różnice w zależności od rodzaju sygnału.

b) Spraw, by w jednym z wątków następowało dzielenie przez zero i by był wygenerowany odpowiedni sygnał. Jak reaguje na niego wątek, który spowodował tę sytuację, a jak inne wątki wchodzące w skład tego samego procesu? Umieść odpowiedź w pliku zad2.raport . Zaznacz dla jakiego rodzaju systemu operacyjnego i wersji jądra były przeprowadzane testy i jaki to był komputer.
