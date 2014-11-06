
   RDM - Dessin - Maillage
   Calcul des Structures par la Méthode des Eléments Finis

   Version  - 6.14 - 22 Janvier 2002

   Utilisateur : Ecole Nationale d'Ing�nieurs - BREST

$debut du fichier
$version
6.14
$SI unites
$nom du fichier
MPmaille.geo
$date
11/10/2012
$points
6
   1  5.00000000000E-02  5.50000000000E-01 1  1.00
   2  5.00000000000E-01  5.50000000000E-01 1  1.00
   3  9.50000000000E-01  5.00000000000E-02 1  1.00
   4  5.00000000000E-02  5.00000000000E-02 1  1.00
   5  5.00000000000E-01  3.00000000000E-01 1  1.00
   6  9.50000000000E-01  3.00000000000E-01 1  1.00
$courbes
segment 1 2 101 1
segment 3 4 101 2
segment 4 1 101 3
segment 5 6 101 4
segment 5 2 101 5
segment 6 3 101 6
//// fin
$fenetre
 7.12803E-04  1.10729E+00  2.76472E-18  6.00000E-01
$maillage
elements 50
lissage 3
jacobien 0.70
////
$fin du fichier
