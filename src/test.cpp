/**
 * @file test.cpp
 * @brief Program file for testing
 */

#include "FR_DICT.h"
#include "preprocess_xml.hpp"

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <vector>

using std::cout;
using std::endl;

std::vector<bool> test_results;
static const std::vector<string> unavailable_test_strings = {
    "agua", "sieaas", "asldj", "apdihanmkasldd", "paisdowjfw", "123", "landi",
    "agua", "sieaas", "asldj", "apdihanmkasldd", "paisdowjfw", "123", "landi",
    "agua", "sieaas", "asldj", "apdihanmkasldd", "paisdowjfw", "123", "landi",
    "agua", "sieaas", "asldj", "apdihanmkasldd", "paisdowjfw", "123", "landi",
    "agua", "sieaas", "asldj", "apdihanmkasldd", "paisdowjfw", "123", "landi",
    "agua", "sieaas", "asldj", "apdihanmkasldd", "paisdowjfw", "123", "landi",
    "agua", "sieaas", "asldj", "apdihanmkasldd", "paisdowjfw", "123", "landi",
    "agua", "sieaas", "asldj", "apdihanmkasldd", "paisdowjfw", "123", "landi",
    "agua", "sieaas", "asldj", "apdihanmkasldd", "paisdowjfw", "123", "landi",
    "agua", "sieaas", "asldj", "apdihanmkasldd", "paisdowjfw", "123", "landi",
    "agua", "sieaas", "asldj", "apdihanmkasldd", "paisdowjfw", "123", "landi",
    "agua", "sieaas", "asldj", "apdihanmkasldd", "paisdowjfw", "123", "landi"};

static const std::vector<string> test_strings = {"accueil",
                                                 "dictionnaire",
                                                 "lire",
                                                 "encyclopédie",
                                                 "manga",
                                                 "ouvrage",
                                                 "siège",
                                                 "chaise",
                                                 "fauteuil",
                                                 "meuble",
                                                 "mardi",
                                                 "lundi",
                                                 "semaine",
                                                 "militaire",
                                                 "suis",
                                                 "barbe à papa",
                                                 "manchot",
                                                 "pingouin",
                                                 "mercredi",
                                                 "bande dessinée",
                                                 "oiseau",
                                                 "allemand",
                                                 "allemande",
                                                 "allemands",
                                                 "jeudi",
                                                 "vendredi",
                                                 "ailé",
                                                 "voler",
                                                 "ovipare",
                                                 "poisson",
                                                 "travail",
                                                 "armée",
                                                 "nouveau",
                                                 "pinyin",
                                                 "sinogramme",
                                                 "kanji",
                                                 "chair à canon",
                                                 "jour",
                                                 "groupe",
                                                 "école",
                                                 "cd-rom",
                                                 "photographie",
                                                 "ordinateur",
                                                 "janvier",
                                                 "année",
                                                 "février",
                                                 "mars",
                                                 "avril",
                                                 "mai",
                                                 "juin",
                                                 "juillet",
                                                 "octobre",
                                                 "novembre",
                                                 "décembre",
                                                 "computer",
                                                 "anglais",
                                                 "lieu",
                                                 "physique",
                                                 "concertation",
                                                 "interrogation",
                                                 "homogène",
                                                 "imprimante",
                                                 "empirique",
                                                 "observation",
                                                 "hypothèse",
                                                 "collaboration",
                                                 "samedi",
                                                 "dimanche",
                                                 "prendre",
                                                 "le",
                                                 "la",
                                                 "les",
                                                 "fin",
                                                 "abréviation",
                                                 "essai",
                                                 "chinois",
                                                 "procrastiner",
                                                 "espagnol",
                                                 "espagnols",
                                                 "neuf",
                                                 "et",
                                                 "un",
                                                 "nord",
                                                 "sud",
                                                 "localisation",
                                                 "terre",
                                                 "dico",
                                                 "je",
                                                 "mot",
                                                 "une",
                                                 "aux",
                                                 "personne",
                                                 "green",
                                                 "plage",
                                                 "lès",
                                                 "nom commun",
                                                 "des",
                                                 "ou",
                                                 "cérémonie",
                                                 "toulouse",
                                                 "on",
                                                 "o",
                                                 "arrivant",
                                                 "japonais",
                                                 "consistant",
                                                 "verbe",
                                                 "accueille",
                                                 "rare",
                                                 "travaux",
                                                 "anglaise",
                                                 "anglaises",
                                                 "portugais",
                                                 "ordre",
                                                 "deux",
                                                 "internet",
                                                 "courriel",
                                                 "pourriel",
                                                 "arriver",
                                                 "ensemble",
                                                 "nom",
                                                 "adjectif",
                                                 "alphabétique",
                                                 "du",
                                                 "traduction",
                                                 "sens",
                                                 "néerlandais",
                                                 "néerlandaises",
                                                 "néerlandais",
                                                 "livre",
                                                 "alphabet",
                                                 "habitant",
                                                 "a",
                                                 "texte",
                                                 "article",
                                                 "langue",
                                                 "élément",
                                                 "unitaire",
                                                 "mobilier",
                                                 "étranger",
                                                 "chat",
                                                 "blog",
                                                 "sujet",
                                                 "au",
                                                 "b",
                                                 "corps",
                                                 "gouvernement",
                                                 "de",
                                                 "généralement",
                                                 "an",
                                                 "chose",
                                                 "région",
                                                 "nommer",
                                                 "animal",
                                                 "a priori",
                                                 "indéfini",
                                                 "calculateur",
                                                 "terme",
                                                 "rédemption",
                                                 "tu",
                                                 "phrase",
                                                 "homonyme",
                                                 "aimer",
                                                 "uns",
                                                 "énergie",
                                                 "électrique",
                                                 "électricité",
                                                 "chas",
                                                 "maçon",
                                                 "charpentier",
                                                 "jeu",
                                                 "gamin",
                                                 "avéré",
                                                 "gamine",
                                                 "mots",
                                                 "system",
                                                 "système",
                                                 "grec",
                                                 "singulier",
                                                 "à",
                                                 "irrégulier",
                                                 "l",
                                                 "il",
                                                 "c",
                                                 "d",
                                                 "e",
                                                 "mon",
                                                 "ton",
                                                 "son",
                                                 "astrométrie",
                                                 "astronomie",
                                                 "entropie",
                                                 "ma",
                                                 "mes",
                                                 "ta",
                                                 "tes",
                                                 "sa",
                                                 "ses",
                                                 "cheval",
                                                 "chevaux",
                                                 "notre",
                                                 "nos",
                                                 "votre",
                                                 "vos",
                                                 "leur",
                                                 "pomme",
                                                 "pomme de terre",
                                                 "aucun",
                                                 "ouf",
                                                 "aïe",
                                                 "argot",
                                                 "slang",
                                                 "oh",
                                                 "aulx",
                                                 "homme",
                                                 "futur",
                                                 "bar",
                                                 "barre",
                                                 "italien",
                                                 "là",
                                                 "unes",
                                                 "ont",
                                                 "avoir",
                                                 "pluriel",
                                                 "marché",
                                                 "catalan",
                                                 "breton",
                                                 "utiliser",
                                                 "en",
                                                 "mandarin",
                                                 "relatif",
                                                 "pays",
                                                 "mois",
                                                 "synonyme",
                                                 "latin",
                                                 "eau",
                                                 "but",
                                                 "elle",
                                                 "traduire",
                                                 "espéranto",
                                                 "éclairci",
                                                 "pas",
                                                 "quintal",
                                                 "nous",
                                                 "finir",
                                                 "bienvenue",
                                                 "éclaircie",
                                                 "auparavant",
                                                 "néanmoins",
                                                 "réseau",
                                                 "logiciel",
                                                 "voiture",
                                                 "enfant",
                                                 "dix",
                                                 "vingt",
                                                 "trente",
                                                 "quinze",
                                                 "blanc",
                                                 "rouge",
                                                 "jaune",
                                                 "hongrois",
                                                 "hongrie",
                                                 "cinq",
                                                 "lui",
                                                 "cardinal",
                                                 "ordinal",
                                                 "premier",
                                                 "lentement",
                                                 "voire",
                                                 "dorénavant",
                                                 "dopage",
                                                 "malveillant",
                                                 "malsain",
                                                 "pareil",
                                                 "fatwa",
                                                 "gestion",
                                                 "discipline",
                                                 "énoncer",
                                                 "fournir",
                                                 "apprivoiser",
                                                 "domestiquer",
                                                 "rendre",
                                                 "échange",
                                                 "extérieur",
                                                 "au-delà",
                                                 "seuil",
                                                 "maison",
                                                 "grand",
                                                 "chatteries",
                                                 "chaton",
                                                 "ronronner",
                                                 "foyer",
                                                 "feu",
                                                 "déploiement",
                                                 "acronyme",
                                                 "sigle",
                                                 "programmation",
                                                 "contrepartie",
                                                 "opérateur",
                                                 "étendu",
                                                 "stocker"};

int main() {
  std::chrono::time_point<std::chrono::system_clock> start, end;
  std::chrono::duration<double> elapsed_seconds;
  cout << "Default run, 300 entries \n";
  unsigned int n = 300;
  cout << "--------------------------------------------------------------------"
          "------"
       << endl;
  cout << "--------------- fr_dict initialization "
          "----------------"
       << endl;
  cout << "--------------------------------------------------------------------"
          "------"
       << endl;
  try {
    fr_dict load_test(n);
  } catch (const std::exception &e) {
    test_results.push_back(false);
    std::cout << e.what();
  }
  fr_dict p(n);
  test_results.push_back(true);

  cout << "--------------------------------------------------------------------"
          "------"
       << endl;
  cout << "--------------- XML pre-processing test "
          "----------------"
       << endl;
  cout << "--------------------------------------------------------------------"
          "------"
       << endl;

  start = std::chrono::system_clock::now();
  p.process_xml(n);
  end = std::chrono::system_clock::now();
  elapsed_seconds = end - start;
  cout << "Seconds to process the xml file: " << elapsed_seconds.count()
       << endl;
  test_results.push_back(true);

  cout << "--------------------------------------------------------------------"
          "------"
       << endl;
  cout << "--------------- Dictionary loading test "
          "----------------"
       << endl;
  cout << "--------------------------------------------------------------------"
          "------"
       << endl;

  start = std::chrono::system_clock::now();
  p.load_dictionary();
  end = std::chrono::system_clock::now();
  elapsed_seconds = end - start;
  cout << "Seconds to store dictionary in heap: " << elapsed_seconds.count()
       << endl;
  test_results.push_back(true);

  cout << "--------------------------------------------------------------------"
          "------"
       << endl;
  cout << "--------------- Dictionary file-loading test "
          "----------------"
       << endl;
  cout << "--------------------------------------------------------------------"
          "------"
       << endl;

  cout << "--------------------------------------------------------------------"
          "------"
       << endl;
  try {
    fr_dict file_load_test(n);
    std::cout << "Loading previous " << n << " entries" << std::endl;
    try {
      start = std::chrono::system_clock::now();
      file_load_test.load_dictionary();
      end = std::chrono::system_clock::now();
      elapsed_seconds = end - start;
      cout << "Seconds to store pre-existing dictionary: "
           << elapsed_seconds.count() << endl;
    } catch (const std::exception &e) {
      test_results.push_back(false);
      std::cout << e.what();
    }
  } catch (const std::exception &e) {
    test_results.push_back(false);
    std::cout << e.what();
  }
  test_results.push_back(true);

  cout << "--------------------------------------------------------------------"
          "------"
       << endl;
  cout << "--------------- Dictionary search test for existing words "
          "----------------"
       << endl;
  cout << "--------------------------------------------------------------------"
          "------"
       << endl;

  long test = 0;

  for (auto string_to_find : test_strings) {
    start = std::chrono::system_clock::now();
    test = p.find_word(string_to_find);
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    if (test != -1) {
      cout << "Found: " << string_to_find << " in line " << test << " in ";
      cout << elapsed_seconds.count() << " seconds" << endl;
    } else {
      cout << "Error! Did not find: " << string_to_find << endl;
      test_results.push_back(false);
    }
  }
  test_results.push_back(true);

  cout << "--------------------------------------------------------------------"
          "------"
       << endl;
  cout << endl;

  cout << "--------------------------------------------------------------------"
          "------"
       << endl;
  cout << "--------------- Search test for not available words "
          "----------------"
       << endl;
  cout << "--------------------------------------------------------------------"
          "------"
       << endl;

  for (auto string_to_find : unavailable_test_strings) {
    start = std::chrono::system_clock::now();
    test = p.find_word(string_to_find);
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    if (test == -1) {
      cout << string_to_find << " not found in ";
      cout << elapsed_seconds.count() << " seconds" << endl;
    } else {
      test_results.push_back(false);
      cout << "Found word that wasn't loaded" << endl;
    }
  }
  test_results.push_back(true);

  cout << "--------------------------------------------------------------------"
          "------"
       << endl;
  cout << "----------------------- Printing dictionary "
          "------------------------------"
       << endl;
  cout << "--------------------------------------------------------------------"
          "------"
       << endl;
  p.print_dictionary();
  cout << "--------------------------------------------------------------------"
          "------"
       << endl;
  cout << endl;

  cout << "--------------------------------------------------------------------"
          "------"
       << endl;
  cout << "----------------------- Printing results "
          "------------------------------"
       << endl;
  cout << "--------------------------------------------------------------------"
          "------"
       << endl;
  int failures = 0;
  for (auto res : test_results) {
    if (!res) {
      cout << "Failed here" << std::endl;
      failures++;
    }
  }
  if (failures == 0) {
    cout << endl;
    cout << endl;
    cout << "ALL TESTS SUCCESSFUL" << endl;
  } else {
        cout << endl;
    cout << endl;
    cout << "FAILED " << failures << " TIMES" << endl;
  }
  cout << "--------------------------------------------------------------------"
          "------"
       << endl;
  cout << endl;

  return 0;
}
