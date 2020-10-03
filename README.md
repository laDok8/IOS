# projekt 1

Popis úlohy

Cílem úlohy je vytvořit skript, který prozkoumá adresář a vytvoří report o jeho obsahu.
Předmětem rekurzivního zkoumání adresáře je počet souborů a adresářů a velikosti souborů. Výstupem skriptu je textový report.
Skript jekonfigurovatelný pomocí příkazové řádky.

Specifikace chování skriptu
JMÉNO
    dirgraph- statistika obsahu adresáře
POUŽITÍ
    dirgraph [-i FILE_ERE] [-n] [DIR]
    
POPIS
1. Pokud byl skriptu zadán adresář (DIR), bude předmětem zkoumání. Bez zadaného adresáře se prozkoumáváaktuální adresář.
2. Přepínač -i způsobuje ignorování souborů a adresářů, jejichž samotný název odpovídá rozšířenému regulárnímuvýrazu FILE_ERE.
FILE_ERE nesmí pokrývat název kořenového adresáře (skript by ignoroval všechny souborya podadresáře).
3. Přepínač -n nastavuje normalizaci histogramu (viz níže).

Součástí reportu je:
- informace o adresářích:
- počet všech adresářů,
- počet všech souborů,
- histogram velikosti souborů,

FORMÁT REPORTU

    Root directory: DIR
    Directories: ND
    All files: NF
    File size histogram:

FSHIST
1. Formát reportu musí přesně (vč. mezer) odpovídat předcházejícímu textu s odpovídajícími čísly.
2. Formát reportu nezahrnuje statistiky ignorovaných souborů či adresářů.
3. DIR je zkoumaný adresář předaný na příkazové řádce při spuštění skriptu. V případě, že skriptu nebyl zadánadresář, je DIR aktuální pracovní adresář (cwd).
4. ND (>0) je počet adresářů v adresářovém stromu.
5. NF (>=0) je počet všech obyčejných souborů.
6. Víceřádkový histogram velikostí souborů FSHIST je vykreslen pomocí ASCII a je otočený doprava: řádek 
histogramu udává kategorii a velikost sloupce (resp. řádku vzhledem k otočení histogramu) dané kategorie udává
počet souborů v dané kategorii. Každý soubor v dané kategorii je reprezentován jedním znakem mřížka # (v
 případě normalizovného histogramu je toto upraveno - viz níže). Každý řádek histogramu začíná dvěma mezerami,
 názvem kategorie, který je zarovnán na stejnou šířku, následované dvojtečkou a mezerou. 
 FSHIST má předemurčené kategorie:
 
- <100 B
- <1 KiB
- <10 KiB
- <100 KiB
- <1 MiB
- <10 MiB
- <100 MiB
- <1 GiB
- \>=1 GiB

7. V případě nastavené normalizace histogramu je velikost vykreslené kategorie (tj. počet mřížek) poměrně upravena
tak, aby celková délka řádku nepřekročila maximální délku řádku. Maximální délka řádku je dána buď délkou
řádku terminálu (pokud je skritp spuštěn v terminálu) minus jeden znak, nebo 79, pokud není výstup skriptu terminál.

NÁVRATOVÁ HODNOTA
Skript vrací úspěch v případě úspěšného zjištění všech informací. Vrátí chybu v případě chyby při zjišťování informací
o souborech či adresářích. V takovém případě skript skončí také s chybovým hlášením

Implementační detaily
* Přítomnost terminálu zjišťujte pomocí utility test. Šířku řádku terminálu pomocítput cols.
* Skript by měl mít v celém běhu nastavenoPOSIXLY_CORRECT=yes.
* Skript by měl běžet na všech běžných shellech (dash, ksh, bash). Ve školním prostředí můžete použít základní(POSIX) /bin/sh.
* Referenční stroj neexistuje. Skript musí běžet na běžně dostupných OS GNU/Linux a *BSD. Ve školním prostředí
máte k dispozici počítače v laboratořích (CentOS), stroj merlin (CentOS) a eva (FreeBSD). Pozor, na stroji
merlin je shell /bin/ksh symbolický odkaz na bash (tj. nechová se jako Korn shell jako na obvyklých strojích).
* Skript nesmí používat dočasné soubory.

Příklady použití
Příklady předpokládají skript dirgraph v cestě spustitelných programů (PATH).

    $ dirgraph /usr/local/bin
    Root directory: /usr/local/bin
    Directories: 1
    All files: 85
    File size histogram:
    <100 B  : #######
    <1 KiB  : ###############
    <10 KiB : ########################################
    <100 KiB: ###################
    <1 MiB  : ###
    <10 MiB : #
    <100 MiB:
    <1 GiB  :
    >=1 GiB :
    
    $ dirgraph -n /etc
    Root directory: /etc
    Directories: 389
    All files: 1766
    File size histogram:
    <100 B  : #####################
    <1 KiB  : ###################################################################
    <10 KiB : ###############################################################
    <100 KiB: ##################
    <1 MiB  : ##
    <10 MiB :
    <100 MiB:
    <1 GiB  :
    >=1 GiB :
    
# projekt 2

A. Popis úlohy
Implementujte v jazyce C modifikovaný synchronizační problém Faneuil Hall Problem (mužete se inspirovat knihou The Little Book of Semaphores).
Existují dva druhy vláken: přistěhovalci (immigrants) a jeden soudce (judge). Přistěhovalci musí čekat ve frontě, vstoupit do soudní budovy, 
zaregistrovat se a pak čekat na rozhodnutí soudce. V určitém okamžiku vstoupí soudce do budovy. Když je soudce v budově, 
nikdo jiný nesmí vstoupit dovnitř ani odejít z budovy. Jakmile se všichni přistěhovalci, ktěrí vstoupili do budovy, zaregistrují, muže soudce 
vydat rozhodnutí (potvrdit naturalizaci). Po vydání rozhodnutí (potvrzení) si přistěhovalci vyzvednou certifikát o občanství USA. 
Soudce odejde z budovy v určitém okamžiku po rozhodnutí. Poté, co přistěhovalci vyzvednou certifikát, mohou odejít.Přistěhovalci vstupují do budovy
jednotlivě (pouze jeden turniket) a také se jednotlivě registrují(pouze jedno registrační místo). Soudce vydává rozhodnutí pro všechny registrované
přistěhovalce naráz. Certifikáty si imigranti vyzvedávají nezávisle na sobě a přítomnosti soudce v budově.

B. Podrobná specifikace úlohy
Spuštění
    $./proj2 PI IG JG IT JT
kde
• PI je počet procesu vygenerovaných v kategorii přistěhovalcu; bude postupně vytvořeno PI immigrants. P>=1
• IG je maximální hodnota doby (v milisekundách), po které je generován nový procesimmigrant. IG>=0&&IG<=2000.
• JG je maximální hodnota doby (v milisekundách), po které soudce opět vstoupí do budovy. JG>=0&&JG<=2000.
• IT je maximální hodnota doby (v milisekundách), která simuluje trvání vyzvedávání certifikátu přistěhovalcem. IT>=0&&IT<=2000.
• JT je maximální hodnota doby (v milisekundách), která simuluje trvání vydávání rozhodnutí soudcem. JT>=0&&JT<=2000.
•Všechny parametry jsou celá čísla.

Implementační detaily
* Pracujte s procesy, ne s vlákny.
* Hlavní proces vytváří ihned po spuštění jeden pomocný proces pro generování procesu přistěhovalcu
a jeden proces pro soudce. Poté čeká na ukončení všech procesu, které aplikace vytváří. Jakmile jsou tyto procesy
ukončeny, ukončí se i hlavní proces s kódem (exit code) 0.
* Generování procesu
  – immigrant: pomocný proces generuje procesy pro immigrants; každý nový proces je generován po uplynutí náhodné doby z intervalu<0,IG>; celkem vygeneruje
  PI procesu. Pokudplatí IG==0, všechny příslušné procesy se vygenerují ihned.
  – Každý takto vygenerovaný proces bude interně identifikován celým číslem I, začínajícím od 1. Číselná řada je pro každou 
  kategorii procesu zvlášť.
  – Postupně tedy vznikne hlavní proces, proces soudce, pomocný proces a PI procesu přistěhovalcu.
* Každý proces vykonává své akce a současně zapisuje informace o akcích do souboru s názvem proj2.out. Součástí výstupních informací o akci
je pořadové číslo A prováděné akce (viz popis výstupu). Akce se číslují od jedničky.
* Použijte sdílenou paměť pro implementaci čítače akcí a sdílených proměnných nutných pro synchronizaci.
* Použijte semafory pro synchronizaci proces ̊u.
* Nepoužívejte aktivní čekání (včetně cyklického časového uspání procesu) pro účely synchronizace.
Chybové stavy
•Pokud některý ze vstup̊u nebude odpovídat očekávanému formátu nebo bude mimo povolený
rozsah, program vytiskne chybové hlášení na standardní chybový výstup,uvolní všechny dosudalokované zdroje a ukončí se s kódem (exit code) 1.

Popis procesů a jejich výstupů
Poznámka k výstupům
 - Aje pořadovéčíslo prováděné akce, 
- NAME je zkratka kategorie příslušného procesu, tj.JUDGEneboIMM,
 - I je interní identifikátor procesu v rámci příslušné kategorie, 
- NE je aktuální počet přistěhovalců, kteří vstoupili do budovy a dosud o nich nebylo rozhodnuto
 - NC je aktuální počet přistěhovalců, kteří se zaregistrovali a dosud o nich nebylo rozhodnuto 
- NB je aktuální počet přistěhovalců, kteří jsou v budově 
- Při vyhodnocování výstupu budou ignorovány mezery a tabelátory. 
Proces osoby (immigrant)
1. Po spuštění tiskneA:NAMEI:starts
2. Pokouší se dostat do budovy(a) Pokud je soudce v budově, čeká, až odejde(b) Pokud není soudce v budově, může vstoupit. Imigranti vstupují jeden po druhém. Ihned  po vstupu tiskne A:NAMEI:enters:NE:NC:NB
.Poznámka: Hodnoty NE a NB zahrnují i tento proces, který právě vstoupil.
3. Registrace(a) Každý procesimmigrantse registruje samostatně (jeden po druhém). Pořadí registrace nemusí odpovídat pořadí vstupu.(b) Ihned po registraci tiskne A:NAMEI: he ks:NE:NC:NB.
Poznámka: Hodnota NC zahrnuje i tento proces, který se právě registroval.
4. Proces čeká na vydání rozhodnutí soudcem.
5. Po vydání rozhodnutí si vyzvedává certifikát
(a) TiskneA:NAMEI:wants ertifi ate:NE:NC:NBa uspí se na náhodnou dobu zintervalu<0,IT>.
(b) Po vzbuzení tiskneA:NAMEI:got certificate:NE:NC:NB.
(c)Poznámka: Hodnoty NE a NC jsou sníženy o počet přistěhovalců, jejichž případ byl právě roz-hodnut soudcem.
6. Odchod budovy
(a) Pokud je soudce v budově,čeká na jeho odchod.
(b) Pokud není soudce v budově, proces tiskne A:NAMEI:leaves:NE:NC:NBa ukončí se.
Poznámka: Hodnota NB reflektuje odchod tohoto procesu z budovy.

Proces osoby (judge)
1. Po spuštění netiskne proces nic.
2. Jakmile je připraven vstoupit do budovy, tj. uplyne náhodná doba z intervalu<0,JG>, tiskne A:NAME:wantstoenter.
3.Jakmile vstoupí do budovy, tiskne A:NAME:enters:NE:NC:NB.
4. Vydání rozhodnutí
(a) Pokud nejsou všichni přistěhovalci, kteří vstoupili do budovy a dosud o nich nebylo rozhod-nuto, registrovaní (NE!=NC)i. Tiskne A:NAME:waitsforimm:NE:NC:NBii. A čeká, až se všichni registrují
(b) Pokud jsou všichni registrovaní (NE==NC)
i. Tiskne A:NAME:starts onfirmation:NE:NC:NB
ii. uspí se na náhodnou dobu z intervalu<0,JT>
iii. poté tiskneA:NAME:ends onfirmation:NE:NC:NB.Poznámka k tomuto vý-stupu: Hodnoty NE a NC jsou sníženy o počet přistěhovalců, jejichž případ byl právě rozhodnut (soudce rozhoduje všechny naráz, takže NE=NC=0).
5. Odchod z budovy(a) Uspí se na náhodnou dobu z intervalu<0,JT>.(b) Poté odchází z budovy a tiskneA:NAME:leaves:NE:NC:NB.
6. Pokud nebyly soudcem zpracovány všechny procesy přistěhovalc ̊u (PI), pokračuje bodem 2. Vopačném případě se ukončí.
7. Pokud byly soudcem zpracovány všechny procesy přistěhovalců (PI), proces soudce se ukončí a tiskne A:NAME:finishes.

#bonus projekt 2
Přepínače
- aplikace bude spuštěna s přepínačem-b(bude vždy na prvním místě)
- hned za přepínačem-bbude doba trvání běhu aplikace (RT) v ms<1,7000>
- počet proces ̊u (PI) bude nyní mít jiný význam - limit počtu proces ̊u imigrant ̊u•ostatní přepínače z ̊ustávají bez změny
Úpravy chování
- jakmile generátor vygeneruje PI proces ̊u přestane generovat procesy a začnečekat na signál po přijetí signálu pokračuje v generování za stejných podmínek (tj. vygeneruje nejvýše PI proces ̊u a opět čeká) generátor bude notifikován (bude mu zaslán signál) poté, co po odchodu imigrant ̊u z ̊ustává budova prázdná (soudce v ní být m ̊uže)
- aplikace běží (generují se procesy imigrant ̊u ařeší se synchronizační úloha) dokud neuběhnedobaRT; poté se dokončí synchronizační úloha pro existující procesy a poté se ukončí i aplikace
–generátor proces ̊u je informován o uběhnutí doby RT prostřednictvím signálu
- aplikaci lze bezpečně ukončit před uplynutím doby RT zasláním signálu SIGQUIT(3) hlavnímu procesu; v reakci na signál postupuje aplikace stejně, jako by uplynula doba RT


