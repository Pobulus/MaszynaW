# Maszyna W

![Maszyna W w programie logisim](https://github.com/Pobulus/MaszynaW/blob/main/image1.png?raw=true)
Maszyna W odtworzona w symulatorze logisim http://www.cburch.com/logisim/

## Czym jest Maszyna W?
Maszyna W to prosty model komputera. Można się o niej więcej dowiedzieć  z artykułu https://minut.polsl.pl/articles/C-19-004.pdf
## Assembler
W pliku `assembler.cpp` znajduje sie kod źródłowy assemblera. Jako plik wejściowy przyjmuje plik tekstowy z kodem w formacie używanym przez maszynę W. Instrukcje zadeklarowane są w pliku `inst.dat` i przydzielane są im rosnące wartości, więc powinny być wpisywane w kolejności zgodnej z tą w pamięci ROM wewnątrz elementu Inst w symulatorze. 

Rozkazy *RPA* i *RST* są zadeklarowane automatycznie i nie należy dodawać ich do pliku `inst.dat`.

Zasemblowany kod zostaje zapisany do pliku o podanej nazwie. Aby uruchomić go w symulatorze należy:
- Wybrać narzędzie zmiany wartości (Ctrl+1 lub ikona palca w pasku narzędzi)
- W obwodzie `main` Kliknąć w element PaO
- Dwukrotnie kliknąć w ikonę lupy
- Kliknąć prawym przyciskiem myszy w element pamięci RAM
- Z menu kontekstowego wybrać `Load Image...`
- Wybrać zasemblowany plik
Po prowrocie do obwodu main, maszyna jest gotowa do pracy.
## Obsługa Symulatora
Dostępne są następujące sygnały sterujące:
- BTN/CLK [0/1] - przełącza między ręcznym taktowaniem a zegarem
- Hand/CPU [0/1] - przełącza między ręcznym ustawianiem sygnałów a wykonywaniem rozkazów
- TAKT - przycisk ręczengo taktowania
- RESET - przycisk do resetowania maszyny
- SYGN - umożliwia ręczne wskazanie, które sygnały mają być aktywne 
Symulator zawiera wyjścia pokazujące aktualne stany rejestrów, oraz diodę wskazującą kiedy pojawił się sygnał stop.
Aby uruchomić maszynę po sygnale stop, należy wyłączyć zegar i przytrzymać przycisk RESET. Gdy dioda STOP zgaśnie, można ponownie uruchomić zegar i program zostanie wykonany od adresu 0.


