#include "french_time.h"

static const char* STR_HEURE = "heure";
static const char* STR_H = " h.";
static const char* STR_MOINS = "moins";
static const char* STR_M = "-- ";

static const char* const HEURES[] = {
  "minuit",
  "une",
  "deux",
  "trois",
  "quatre",
  "cinq",
  "six",
  "sept",
  "huit",
  "neuf",
  "dix",
  "onze",
  "midi"
};

static const char* const MINS[] = {
  "pile !",
  "cinq",
  "dix",
  "et quart",
  "vingt",
  "et demi",
  "le quart",
  "..."
};

static const char* const JOURS[] = {
  "Dimanche",
  "Lundi",
  "Mardi",
  "Mercredi",
  "Jeudi",
  "Vendredi",
  "Samedi"
};

static const char* const MOIS[] = {
  "Jan.",
  "Fév.",
  "Mars",
  "Avril",
  "Mai",
  "Juin",
  "Juil.",
  "Août",
  "Sep.",
  "Oct.",
  "Nov.",
  "Déc."
};



void fuzzy_time(PblTm* t, char* line1, char* line2, char* line3) {

  int hours = t->tm_hour;
  int minutes = t->tm_min;

  strcpy(line1, "");
  strcpy(line2, "");
  strcpy(line3, "");



  if (minutes >= 33) hours++;
  if (hours >= 24) hours = 0;
  if (hours > 12) hours -= 12;

  strcat(line1, HEURES[hours]); // l'HEURE

  if (minutes >= 0 && minutes < 3) {
    if(hours > 0 && hours < 12) {
        strcat(line2, STR_HEURE);
      if (hours > 1) strcat(line2, "s");
    }
    if (minutes == 0) strcat(line3, MINS[0]); // pile !
  }
  else if (minutes < 8) {
    if(hours > 0 && hours < 12) {
        strcat(line2, STR_HEURE);
      if (hours > 1) strcat(line2, "s");
    }
    strcat(line3, MINS[1]); // cinq
  }
  else if (minutes < 13) {
    if(hours > 0 && hours < 12) {
        strcat(line2, STR_HEURE);
      if (hours > 1) strcat(line2, "s");
    }
    strcat(line3, MINS[2]); // dix
  }
  else if (minutes < 18) {
    if(hours > 0 && hours < 12) {
        strcat(line2, STR_HEURE);
      if (hours > 1) strcat(line2, "s");
    }
    strcat(line3, MINS[3]); // et quart
  }
  else if (minutes < 23) {
    if(hours > 0 && hours < 12) {
        strcat(line2, STR_HEURE);
      if (hours > 1) strcat(line2, "s");
    }
    strcat(line3, MINS[4]); // vingt
  }
  else if (minutes < 28) {
    if(hours > 0 && hours < 12) strcat(line1, STR_H);
    strcat(line2, MINS[4]); // vingt
    strcat(line3, MINS[1]); // cinq
  }
  else if (minutes < 33) {
    if(hours > 0 && hours < 12) {
        strcat(line2, STR_HEURE);
      if (hours > 1) strcat(line2, "s");
    }
    strcat(line3, MINS[5]); // et demi
  }
  else if (minutes < 38) {
    if(hours > 0 && hours < 12) strcat(line1, STR_H);
    strcat(line2, STR_M); // --
    strcat(line2, MINS[4]); // vingt
    strcat(line3, MINS[1]); // cinq
  }
  else if (minutes < 43) {
    if(hours > 0 && hours < 12) strcat(line1, STR_H);
    strcat(line2, STR_MOINS);
    strcat(line3, MINS[4]); // vingt
  }
  else if (minutes < 48) {
    if(hours > 0 && hours < 12) strcat(line1, STR_H);
    strcat(line2, STR_MOINS);
    strcat(line3, MINS[6]); // le quart
  }
  else if (minutes < 53) {
    if(hours > 0 && hours < 12) strcat(line1, STR_H);
    strcat(line2, STR_MOINS);
    strcat(line3, MINS[2]); // dix
  }
  else if (minutes < 58) {
    if(hours > 0 && hours < 12) strcat(line1, STR_H);
    strcat(line2, STR_MOINS);
    strcat(line3, MINS[1]); // cinq
  }
  else if (minutes >= 58) {
    strcpy(line1, MINS[7]); // presque
    strcat(line2, HEURES[hours]);
    if(hours > 0 && hours < 12) {
        strcat(line3, STR_HEURE);
      if (hours > 1) strcat(line3, "s");
    }
  }

}

void info_lines(PblTm* t, char* line1, char* line2) {

  char wday[LINE_BUFFER_SIZE];
  char mday[LINE_BUFFER_SIZE];
  char mon[LINE_BUFFER_SIZE];

  strcpy(line1, "");
  strcpy(line2, "");

//  string_format_time(line1, LINE_BUFFER_SIZE, "%A • %e %b", t);
  mini_snprintf(wday, LINE_BUFFER_SIZE, "%s", JOURS[t->tm_wday]);
  mini_snprintf(mday, LINE_BUFFER_SIZE, "%d", t->tm_mday);
  mini_snprintf(mon, LINE_BUFFER_SIZE, "%s", MOIS[t->tm_mon]);
  strcat(line1, wday);
  strcat(line1, " ");
  strcat(line1, mday);
  strcat(line1, " ");
  strcat(line1, mon);

  string_format_time(line2, LINE_BUFFER_SIZE, "s-%W • j-%j • %H%M%S", t);

}



























