// '//α' oder '//ω' als Kommentar sind nur fuer die Verwendung dieses Programms als Programmvorlage wichtig
const double& versnr= //α
#include "versdt"
;
#include "kons.h" //α
#include "DB.h" 
#include <tiffio.h>
#define VOMHAUPTCODE // um Funktionsdefinition manchmal mit "__attribute__((weak)) " versehen zu können //ω
#include "labpath.h"
#include "iconvc.h"
// fuer verschiedene Sprachen //α
char const *DPROG_T[T_MAX+1][SprachZahl]=
{
	// T_virtVorgbAllg
	{"virtVorgbAllg()","virtgeneralprefs()"},
	// T_pvirtVorgbSpeziell
	{"pvirtVorgbSpeziell()","pvirtspecialprefs()"},
	// T_virtMusterVorgb
	{"virtMusterVorgb()","virtsampleprefs"},
	// T_pvirtvorrueckfragen
	{"pvirtvorrueckfragen()","pvirtbeforecallbacks()"},
	// T_virtrueckfragen
	{"virtrueckfragen()","virtcallbacks()"},
	//	T_Fehler_beim_Pruefen_von
	{"Fehler beim Pruefen von: ","Error while examining: "},
	// T_Fuege_ein
	{"Fuege ein: ","Inserting: "}, //ω
	// T_eindeutige_Identifikation
	{"eindeutige Identifikation","unique identifier"},
	// T_Laborparameter
	{"Laborparameter","lab parameter"},
	// T_LWert
	{"Wert","value"},
	// T_Einheit
	{"Einheit","unit"},
	// T_Vorwert_1
	{"Vorwert 1","previous value 1"},
	// T_Vorwert_2
	{"Vorwert 2","previous value 2"},
	// T_Normbereich
	{"Normbereich","normal range"},
	// T_HinweisedL
	{"Hinweise des Labors","hints of the lab"},
	// T_Hinweise
	{"Hinweise","hints"},
	// T_fehlende_ICDs
	{"fehlende ICDs","missing ICDs"},
	// T_Termine
	{"Termine","appointments"},
	// T_Laborwert
	{"(path.) Laborwert","pathol.lab value"},
	// T_quellvz
	{"Quellverzeichnis","sourcedir"},
	// T_pruefdb_k,
	{"pruefdb","checkdb"},
	// T_pruefdb_l,
	{"pruefdb","checkdb"},
	// T_initialisiert_nur_die_Tabellen
	{"initialisiert nur die Tabellen","initializes only the tables"},
	// T_Einlesedatum
	{"Einlesedatum","date of parsing"},
	// T_Pfad,
	{"Pfad","path"},
	// T_Name,
	{"Name","name"},
	// T_Groesse
	{"Größe","size"},
	// T_Aenderungsdatum
	{"Änderungsdatum","date of last change"},
	// T_dfertig,
	{"Daten fertig eingetragen","data completely written"},
	// T_Path_Labor_Einlesungen
	{"Pathologische Laborwert-Dateien-Einlesungen","readings of files with pathological lab values"},
	// T_qvz_k,
	{"qvz","sd"},
	// T_qvz_l,
	{"quellvz","sourcedr"},
	// T_Verzeichnis_der_Quelldateien,
	{"Verzeichnis der Quelldateien","directory of the source files"},
	// T_Verzeichnis_der_einzulesenden_Dateien,
	{"Verzeichnis der einzulesenden Dateien","directory of the files to read"},
	// T_prueflpath,
	{"prueflpath()","testlpath()"},
	// T_prueflpatel,
	{"prueflpatel()","testlpatel()"},
	// T_ID_der_Einlesung
	{"ID der Einlesung","id of the reading"},
	// T_fertig
	{"fertig!","finished!"},
	// T_Dateien_gefunden
	{"Dateien gefunden: ","Files found: "},
	// T_Parse
	{"Parse: ","Parsing: "},
	// T_Patient,
	{"   Patient: ","   Patient: "},
	// T_namsp,
	{"Farbe für Namensspalte","color for name column"},
	// T_wertsp,
	{"Farbe für Wertspalten","color for value columns"},
	// T_hinwsp,
	{"Farbe für Hinweisspalten","color for clou columns"},
	// T_termsp,
	{"Farbe für Terminspalte","color for appointment column"},
	// T_ficdsp
	{"Farbe für fehlende ICD-Spalte","color for missing icds-column"},
	{"",""} //α
}; // char const *DPROG_T[T_MAX+1][SprachZahl]=

class TxB Tx((const char* const* const* const*)DPROG_T);
const char *logdt="/var/log/" DPROG "vorgabe.log";//darauf wird in kons.h verwiesen;

using namespace std; //ω

// von https://stackoverflow.com/questions/3152241/case-insensitive-stdstring-find
// templated version of my_equal so it could work with both char and wchar_t
template<typename charT>
struct my_equal {
    my_equal( const std::locale& loc ) : loc_(loc) {}
    bool operator()(charT ch1, charT ch2) {
        return std::toupper(ch1, loc_) == std::toupper(ch2, loc_);
    }
private:
    const std::locale& loc_;
};

// find substring (case insensitive)
template<typename T>
int iinstr( const T& str1, const T& str2, const std::locale& loc = std::locale() )
{
    typename T::const_iterator it = std::search( str1.begin(), str1.end(), 
        str2.begin(), str2.end(), my_equal<typename T::value_type>(loc) );
    if ( it != str1.end() ) return it - str1.begin();
    else return -1; // not found
}

hhcl::hhcl(const int argc, const char *const *const argv):dhcl(argc,argv,DPROG,/*mitcron*/1) //α
{
	//ω
} // hhcl::hhcl //α
// Hier neue Funktionen speichern: //ω
//α
// wird aufgerufen in lauf
void hhcl::virtVorgbAllg()
{
	hLog(violetts+Tx[T_virtVorgbAllg]+schwarz); //ω
	dhcl::virtVorgbAllg(); //α
} // void hhcl::virtVorgbAllg

// wird aufgerufen in lauf
void hhcl::pvirtVorgbSpeziell()
{
	hLog(violetts+Tx[T_pvirtVorgbSpeziell]+schwarz); //ω
	dhcl::pvirtVorgbSpeziell(); //α
	virtMusterVorgb();
} // void hhcl::pvirtVorgbSpeziell

// wird aufgerufen in lauf
void hhcl::virtinitopt()
{ //ω
	opn<<new optcl(/*pptr*/&nurpruefdb,/*art*/puchar,T_pruefdb_k,T_pruefdb_l,/*TxBp*/&Tx,/*Txi*/T_initialisiert_nur_die_Tabellen,/*wi*/0,/*Txi2*/-1,/*rottxt*/string(),/*wert*/1,/*woher*/1);
	opn<<new optcl(/*pname*/"quellvz",/*pptr*/&quellvz,/*art*/pverz,T_qvz_k,T_qvz_l,/*TxBp*/&Tx,/*Txi*/T_Verzeichnis_der_Quelldateien,/*wi*/0,/*Txi2*/-1,/*rottxt*/string(),/*wert*/-1,/*woher*/!quellvz.empty(),Tx[T_Verzeichnis_der_einzulesenden_Dateien]);
	dhcl::virtinitopt(); //α
} // void hhcl::virtinitopt

// wird aufgerufen in lauf
void hhcl::pvirtmacherkl()
{
	erkl<<blau<<Txk[T_Program]<<violett<<DPROG //ω
		<<blau<<" ist etwas ganz Spezielles"<<schwarz; //α
	tabnamen();
} // void hhcl::pvirtmacherkl

void hhcl::prueftbl()
{
	const size_t aktc{0};
	if (!My) initDB();
	prueflpatel(My, aktc, obverb, oblog, /*direkt*/0);
	prueflpath(My, aktc, obverb, oblog, /*direkt*/0);
} // void hhcl::prueftbl

void hhcl::tabnamen()
{
	labpatel="labpatel";
	labpath="labpath";
} // void hhcl::tabnamen

// wird aufgerufen in: prueftbl
void hhcl::prueflpatel(DB *My, const size_t aktc, const int obverb, const int oblog, const uchar direkt/*=0*/)
{
	hLog(violetts+Tx[T_prueflpatel]+schwarz);
	if (!direkt) {
		Feld felder[] = {
			Feld("ID","int","10","",Tx[T_eindeutige_Identifikation],1,1,0,string(),1),
			Feld("Datum","datetime","0","0",Tx[T_Einlesedatum],0,0,1),
			Feld("Pfad","varchar","100","",Tx[T_Pfad],0,0,1),
			Feld("Name","varchar","100","",Tx[T_Name],0,0,1),
			Feld("Größe","int","12","",Tx[T_Groesse],0,0,1),
			Feld("Änderungsdatum","datetime","0","0",Tx[T_Aenderungsdatum],0,0,1),
			Feld("fertig","bit","","",Tx[T_dfertig],0,0,1),
		};
		Feld ifelder1[] = {Feld("Datum")};   Index i1("Datum",ifelder1,elemzahl(ifelder1));
		Feld ifelder2[] = {Feld("Name"),Feld("Pfad")};   Index i2("Pfad",ifelder2,elemzahl(ifelder2));
		Index indices[]={i1,i2};
		Tabelle taba(My,labpatel,felder,elemzahl(felder),indices,elemzahl(indices),0,0,Tx[T_Path_Labor_Einlesungen]/*//,"InnoDB","utf8","utf8_general_ci","DYNAMIC"*/);
		if (taba.prueftab(aktc,obverb)) {
			fLog(rots+Tx[T_Fehler_beim_Pruefen_von]+schwarz+labpatel,1,1);
			exit(11);
		}
	}
} // prueflpath

// wird aufgerufen in: prueftbl
void hhcl::prueflpath(DB *My, const size_t aktc, const int obverb, const int oblog, const uchar direkt/*=0*/)
{
	hLog(violetts+Tx[T_prueflpath]+schwarz);
	if (!direkt) {
		Feld felder[] = {
			Feld("ID","int","10","",Tx[T_eindeutige_Identifikation],1,1,0,string(),1),
			Feld("elID","int","10","",Tx[T_ID_der_Einlesung],/*obind*/1,/*obauto*/0,/*nnull*/1,/*vdefa*/string(),/*unsig*/1),
		  Feld("Pat_id","int","6","","",0,0,1),
			Feld("Name","varchar","20","",Tx[T_Name],0,0,1),
			Feld("Parameter","varchar","50","",Tx[T_Laborparameter],0,0,1),
			Feld("Wert","varchar","20","",Tx[T_LWert],0,0,1),
			Feld("Einheit","varchar","20","",Tx[T_Einheit],0,0,1),
			Feld("Vorwert_1","varchar","30","",Tx[T_Vorwert_1],0,0,1),
			Feld("Vorwert_2","varchar","30","",Tx[T_Vorwert_2],0,0,1),
			Feld("Normbereich","varchar","300","",Tx[T_Normbereich],0,0,1),
			Feld("Labhinw","varchar","60","Hinweis des Labors",Tx[T_HinweisedL],0,0,1),
			Feld("Hinweise","varchar","60","",Tx[T_Hinweise],0,0,1,""),
			Feld("fICD","varchar","60","",Tx[T_fehlende_ICDs],0,0,1,""),
		  Feld("namsp","int","10","",Tx[T_namsp],0,0,1),
		  Feld("wertsp","int","10","",Tx[T_wertsp],0,0,1),
		  Feld("hinwsp","int","10","",Tx[T_hinwsp],0,0,1),
		  Feld("termsp","int","10","",Tx[T_termsp],0,0,1),
		  Feld("fICDsp","int","10","",Tx[T_ficdsp],0,0,1),
			Feld("Termine","longtext","","",Tx[T_Termine],0,0,1),
		};
		Feld ifelder1[] = {Feld("Pat_id"),Feld("Parameter")}; Index i1("Patid_Par",ifelder1,elemzahl(ifelder1));
		Index indices[]={i1};
		Constraint csts[]{
			Constraint(labpath+labpatel,new Feld{Feld("elID")},1,labpatel,new Feld{Feld("ID")},1,cascade,cascade),
		};
		// auf jeden Fall ginge "binary" statt "utf8" und "" statt "utf8_general_ci"
		Tabelle taba(My,labpath,felder,elemzahl(felder),indices,elemzahl(indices),csts,elemzahl(csts),Tx[T_Laborwert]/*//,"InnoDB","utf8","utf8_general_ci","DYNAMIC"*/);
		if (taba.prueftab(aktc,obverb)) {
			fLog(rots+Tx[T_Fehler_beim_Pruefen_von]+schwarz+labpath,1,1);
			exit(11);
		}
	} // if (!direkt)
} // int pruefouttab(DB *My, string touta, int obverb, int oblog, uchar direkt=0)

// wird aufgerufen in lauf
void hhcl::virtMusterVorgb()
{
	hLog(violetts+Tx[T_virtMusterVorgb]+schwarz); //ω
	dhcl::virtMusterVorgb(); //α
	dbq="quelle";
	quellvz="/DATA/Patientendokumente/SchadeLabor";
} // void hhcl::MusterVorgb

// wird aufgerufen in lauf
void hhcl::pvirtvorzaehler()
{ //ω
} // void hhcl::virtvorzaehler() //α
//ω

// wird aufgerufen in lauf
void hhcl::virtzeigversion(const string& ltiffv/*=nix*/)
{
	dhcl::virtzeigversion(ltiffv); //α
} // void hhcl::virtzeigversion

// wird aufgerufen in lauf
void hhcl::pvirtvorrueckfragen()
{
	hLog(violetts+Tx[T_pvirtvorrueckfragen]+schwarz);
	if (rzf) { //ω
	}
	//α
} // void hhcl::pvirtvorrueckfragen

// wird aufgerufen in lauf
void hhcl::virtpruefweiteres()
{ //ω
	hcl::virtpruefweiteres(); // z.Zt. leer //α
} // void hhcl::virtpruefweiteres

// wird aufgerufen in lauf
void hhcl::virtzeigueberschrift()
{ //ω
	// hier ggf. noch etwas an 'uebers' anhaengen //α
	uebers<<" (Einlesung pathologischer Laborwerte) ";
	hcl::virtzeigueberschrift();
} // void hhcl::virtzeigueberschrift

void hhcl::pvirtnachrueckfragen()
{
} // void hhcl::pvirtnachrueckfragen


bool getasciiline(mdatei& mdat,string& zeile)
{
	string zwi;
	bool glerg{0};
	static iconvc i("ISO-8859-1","UTF-8//TRANSLIT");
  if (getline(mdat,zwi)) {
		if (zwi.length()) {
			zeile=i.convert(zwi);
			glerg=true; 
		}
	}
	if (!glerg) zeile.clear();
	return glerg;
} // getasciiline

#ifdef false
string ausg(string str)
{
	iconvc i("ISO-8859-1","UTF-8//TRANSLIT");
	return i.convert(str);
    char *q=(char*)str.c_str();
		char *dest = new char[2*str.length()];
    size_t outbytes = sizeof dest;
    size_t inbytes = strlen(q);
    iconv_t conv = iconv_open("UTF-8//TRANSLIT", "ISO-8859-1");
    if (conv == (iconv_t)-1) {
        return str;
//        perror("iconv_open");
    }
    if (iconv(conv, &q, &inbytes, &dest, &outbytes) == (size_t)-1) {
        return str;
//        perror("iconv");
    }
    dest[sizeof dest- outbytes] = 0;
    return string(dest);
		string ret{dest};
		delete dest;
		return ret;
}
#endif

// wird aufgerufen in lauf
void hhcl::pvirtfuehraus()
{ //ω
	auto altZDB{ZDB};
	string datid; // Rueckmeldung des eindeutigen Kennzeichens des geschriebenen Datensatzes
	svec eindfeld;
	int geprueft{0}; // 1 = die Tabellen labpathel und labpath wurden schon geprueft, eindfeld schon festgelegt
	//	ZDB=1;
	const size_t aktc{0};
	// unsigned long verarbeitet{0};
	if (rzf) tabnamen(); // nach rueckfragen
	if (nurpruefdb) { // Kommandozeilenparameter
		prueftbl();
	} else {
		pruefverz(quellvz,obverb,oblog);
		svec lrue;
		// alle csv-Dateien im quellvz
		systemrueck("find "+quellvz+" -maxdepth 1 -type f -iname '*.csv' -printf '%TY%Tm%Td%TH%TM%TS\t%p\n' "
				+string(obverb?"":"2>/dev/null")+"|sort|cut -f2", obverb,oblog,&lrue,/*obsudc=*/0);
		if (!stumm) fLog(blaus+Tx[T_Dateien_gefunden]+schwarz+ltoan(lrue.size()),1,oblog);
		for(size_t i=0;i<lrue.size();i++) {
			if (!geprueft) {
				prueftbl();
				geprueft=1;
				eindfeld<<"id";
			} // 			if (!geprueft)
			string *aktl{&lrue[i]};
			RS nachschau(My,"SELECT Datum FROM `"+labpatel+"` WHERE name="+sqlft(My->DBS,base_name(*aktl)),aktc,ZDB);
			if (!nachschau.obqueryfehler) {
				char ***cerg{0};
				if (!(cerg=nachschau.HolZeile())||!*cerg) {
					if (!stumm) fLog(Tx[T_Parse]+blaus+*aktl+schwarz,1,oblog);
					insv reing(My,/*itab*/labpatel,aktc,/*eindeutig*/0,eindfeld,/*asy*/0,/*csets*/0);
					/*auto*/chrono::system_clock::time_point jetzt=chrono::system_clock::now();
          struct stat dstat{0};
					const int dgibts{!lstat(aktl->c_str(),&dstat)};
					if (dgibts) {
						auto groesse{dstat.st_size};
						auto aedat{dstat.st_mtime};

						reing.hz("Name",base_name(*aktl));
						reing.hz("Pfad",dir_name(*aktl));
						reing.hz("Datum",&jetzt);
						reing.hz("Größe",groesse);
						reing.hz("Änderungsdatum",&aedat);
						reing.schreib(/*sammeln*/0,/*obverb*/obverb,/*idp*/&datid);

						mdatei mdat(*aktl,ios::in);
						string zeile;
						if (mdat.is_open()) {
							uchar obanf{0};
							string erstl, altnn,altvn;
							// jede Zeile der csv-Datei lesen
							while(getasciiline(mdat,zeile)) {
								fLog(rots+zeile+schwarz,obverb);
								//							<<rot<<ausg(zeile)<<schwarz<<endl;
								char innen{0}, ch;
								svec erg;
								size_t i{0};
								erg<<"";
								// mehrere Zeilen nötigenfalls zusammenfassen
								while (1) {
									// Zeilenumbrueche in Strings in '|' umwandeln
									for(size_t i=0;i<zeile.length();i++) {
										ch=zeile[i];
										if (ch==10 || ch==13) {
											if (innen) erg[erg.size()-1]+='|'; 
										} else if (!innen && ch==',') {
											erg<<"";
										} else if (ch=='"') {
											innen=!innen;
										} else {
											erg[erg.size()-1]+=ch; 
											// s<<gruen<<"ch: "<<ch<<" erg.size(): "<<erg.size()<<" erg.size()-1: "<<erg.size()-1<<
											//   " erg[erg.size()-1]: "<<erg[erg.size()-1]<<schwarz<<" innen: "<<(int)innen<<endl;
										}
									} // 								for(size_t i=0;i<zeile.length();i++)
									if (!innen) break;
									if (!getasciiline(mdat,zeile)) break;
									fLog("i: "+ltoan(i)+" "+rot+zeile+schwarz,obverb);
								} // 							while (1)
								for(size_t i=0;i<erg.size();i++) {
									if (erg[i]!="")
										fLog("i: "+ltoan(i)+" "+blau+erg[i]+schwarz,obverb>1);
								} // 							for(size_t i=0;i<erg.size();i++)
								insv reine(My,/*itab*/labpath,aktc,/*eindeutig*/0,eindfeld,/*asy*/0,/*csets*/0);
								svec nteile;
								aufSplit(&nteile, erg[0]);
								if (!obanf) {
									if (erg[0].find("Erstellt")!=string::npos) {
										erstl=nteile[nteile.size()-1];
										obanf=1;
									}
								} else if (obanf==1) {
									if (erg[0].find("Patient")!=string::npos) {
										obanf=2;
									}
								} else {
									uchar obname{0},obpid{0};
									string pid,gschl,abkue,einh,wert,mfmg,hinw,ficd;
									double vorwert;
									long hinwsp{16777215}, ficdsp{16777215};
									if (nteile[nteile.size()-1]!=altnn || nteile[0]!=altvn) {
										altnn=nteile[nteile.size()-1];
										altvn=nteile[0];
										if (!stumm) fLog(Tx[T_Patient]+blaus+altnn+", "+altvn+schwarz,1,oblog);
									}
									string itv;
									// verschiedene Intervalle von Patientenfaellen rueckwaerts, um genau einen Patienten dieses Namens zu finden
									for(unsigned iru=0;iru<3;iru++) {
										// <<rot<<"          iru: "<<violett<<iru<<schwarz<<endl;
										switch (iru) {case 0: itv="4";break; case 1: itv="100";break; case 2: itv="10000";break;}
										string nname, vname;
										// 2 verschiedene Identitaeten von Vor- und Nachname
										for(unsigned aru=0;aru<2;aru++) {
											// <<rot<<"           aru: "<<violett<<aru<<schwarz<<endl;
											if (aru) {vname=nname;nname=altvn;} else {nname=ersetzAllezu(altnn,"'","''");vname=altvn;}
											RS pd(My,"SELECT COUNT(1) OVER() zl, f.pat_id, CONCAT(gesname(f.pat_id),' (',patalter(f.pat_id),')'),geschlecht"
													",patalter(f.pat_id),COALESCE(s.voret,0) voret "
													"FROM faelle f "
													"LEFT JOIN namen n USING (pat_id) "
													"LEFT JOIN sws s ON s.pat_id=p.pat_id AND s.voret>f.qanf"
													"WHERE n.nachname='"+nname+"' AND n.vorname LIKE '"+vname+"%' "
													"AND BhFB<STR_TO_DATE('"+erstl+"','%d.%m.%Y') AND "
													"(BhFE1>ADDDATE(STR_TO_DATE('"+erstl+"','%d.%m.%Y'),-"+itv+") OR BhFE1=18991230) "
													"GROUP BY f.pat_id;",aktc,ZDB);
											//										if (altnn=="....") caus<<blau<<pd.sql<<schwarz<<endl;
											// <<"        Nachame: "<<blau<<nname<<", "<<vname<<schwarz;
											if (pd.obqueryfehler) {
												// <<pd.sql<<endl;
											} else {
												long palter{0};
												const char *const *const *const ferg{pd.HolZeile()};
												if (!(ferg?*ferg:0)) {
													// <<", ferg: "<<ferg<<endl;
													// <<violett<<pd.sql<<schwarz<<endl;
												} else {
													const long zl{atol(cjj(ferg,0))};
													// <<", gefunden: "<<violett<<zl<<schwarz<<endl;
													if (zl<1 && !(iru==2 && aru==1)) goto naeiru; // wenn bei einem nicht letzten Durchlauf nichts gefunden wurde, nichts eintragen
													palter=atol(cjj(ferg,4));
													// einen Patienten gefunden:
													if (zl==1) {
														iru=(unsigned)-2; // als nächstes große Schleife abbrechen
														pid=cjj(ferg,1);
														reine.hz("Pat_id",cjj(ferg,1));
														if (ferg[2]) {
															reine.hz("Name",cjj(ferg,2));
															obname=1;
														}
														if (ferg[3]) gschl=cjj(ferg,3);
														// mehrere Patienten gefunden:
													} else if (zl>1) {
														iru=(unsigned)-2; // als nächstes große Schleife abbrechen
														// Patientennr und -name holen und schauen, ob er eindeutig ist
														RS npid(My,"SELECT COUNT(1) OVER() zl, l.pat_id, CONCAT(gesname(l.pat_id),' (',patalter(l.pat_id),')'),geschlecht "
																"FROM labor2a l LEFT JOIN namen n USING(pat_id)"
																"WHERE l.pat_id IN (SELECT pat_id FROM namen "
																"WHERE TRIM(CONCAT(titel,' ',vorname,' ',nvors, if(nvors='','',' '),nachname)) = "
																"'"+nteile[nteile.size()-1]+"')"
																"AND zeitpunkt BETWEEN DATE_SUB(STR_TO_DATE('"+erstl+"','%d.%m.%Y'),INTERVAL 7 DAY) "
																"AND DATE_ADD(STR_TO_DATE('"+erstl+"','%d.%m.%Y'),INTERVAL 1 DAY) "
																"ORDER BY zeitpunkt DESC",aktc,ZDB); 
														if (!npid.obqueryfehler) {
															const char *const *const *const lerg{npid.HolZeile()};
															if (lerg?*lerg:0) {
																if (!strcmp(cjj(lerg,0),"1")) {
																	pid=cjj(lerg,1);
																	reine.hz("Pat_id",cjj(lerg,1));
																	if (lerg[2]) {
																		reine.hz("Name",cjj(lerg,2));
																		obname=1;
																	}
																	if (lerg[3]) gschl=cjj(lerg,3);
																} // 													if (!strcmp(cjj(lerg,0),"1"))
															} // 												while (lerg=npid.HolZeile(),lerg?*lerg:0)
														} // if (!npid.obqueryfehler)
													} // if (!strcmp(cjj(ferg,0),"1")) ... else if (strcmp(cjj(ferg,0),"0"))
													obpid=(pid!="");
													if (!obname)
														reine.hz("Name",erg[0]);
													// nach dem Namen noch die anderen Einzelheiten festlegen:
													if (1) {
														reine.hz("elID",datid);
														size_t p1,p2,p3,p4;
														uchar pz{2},oblh{0};
														if ((p1=erg[1].find(':'))!=string::npos) {
															abkue=erg[1].substr(0,p1);
															reine.hz("Parameter",abkue);
															if ((p2=erg[1].find(' ',p1+2))!=string::npos) { // MAK: |<600
																if (erg[1][p1+1]==' ') p1++;
																if (erg[1][p1+1]=='|') p1++;
																wert=erg[1].substr(p1+1,p2-p1-1);
																reine.hz("Wert",wert);
																if ((p3=erg[1].find('(',p2))!=string::npos) {
																	einh=erg[1].substr(p2+1,p3-p2-2);
																	reine.hz("Einheit",einh);
																	p4=erg[1].find("|",p3);
																	if (p4!=string::npos) {
																		reine.hz("Normbereich",erg[1].substr(p3+1,p4-p3-1));
																		p3=p4;
																		oblh=1;
																	}
																	p4=erg[1].find(" / ",p3);
																	if (p4==string::npos) {
																		p4=erg[1].rfind(")");
																		pz=1;
																	}
																	if (p4!=string::npos) {
																		reine.hz(oblh?"Labhinw":"Normbereich",erg[1].substr(p3+1,p4-p3-(oblh?pz:1)));
																	}
																	if (!oblh)
																		reine.hz("Labhinw","");
																} // 											if ((p3=erg[1].find('(',p2))!=string::npos)
															} // 										if ((p2=erg[1].find(' ',p1))!=string::npos)
														} // 									if ((p1=erg[1].find(':'))!=string::npos)
														vorwert=0;
														if (obpid) {
															RS fb(My,"SELECT "
																	" CASE "
																	"  WHEN TKZ<>0 AND GSZ=0 AND wdz=0 AND ahz=0 THEN 14772545 "//vbmittelblau, RGB(65, 105, 225) ' http://www.am.uni-duesseldorf.de/de/Links/Tools/farbtabelle.html

																	"  WHEN tkz=0 AND gsz<>0 AND wdz=0 AND ahz=0 THEN 65535 " // gelb, &HFFFF&
																	"  WHEN tkz=0 AND gsz=0 AND ahz<>0 THEN 8553215 " // vbwagnerahrot, RGB(255,130,130), 
																	"  WHEN tkz=0 AND gsz=0 AND wdz<>0 THEN 6974207 " // vbwagnerrot, RGB(255,106,106), 
																	"  WHEN tkz<>0 AND gsz<>0 AND wdz=0 and ahz=0 THEN 7451452 " // vbwagnergrün, RGB(60,179,113)
																	"  WHEN tkz<>0 AND gsz=0 AND (wdz<>0 OR ahz<>0) THEN 13850042 "// vbmittellila, rgb(186,85,211)
																	"  WHEN tkz=0 AND gsz<>0 AND (wdz<>0 OR ahz<>0) THEN 33023 " // orange, &H80FF&
																	"  WHEN tkz<>0 AND gsz<>0 AND (wdz<>0 OR ahz<>0) THEN 755384 " // vbmittelbraun, RGB(184,134,11)
																	"  ELSE 16777215 " // FFFFFF
																	" END namsp,"
																	" CASE "
																	"  WHEN TKZ<>0 AND GSZ=0 AND WDZ=0 and ahz=0 THEN 16767449 " // hellblau, &HFFD9D9
																	"  WHEN tkz=0 AND gsz<>0 AND wdz=0 and ahz=0 THEN 12648447 "// vbhellgelb, &HC0FFFF
																	"  WHEN tkz=0 AND gsz=0 AND ahz<>0 THEN 11195135 "// mittigahrosa, &HFFD2AA 
																	"  WHEN tkz=0 AND gsz=0 AND wdz<>0 THEN 12632319 "// mittigrosa, &HC0C0FF
																	"  WHEN tkz<>0 AND gsz<>0 AND wdz=0 and ahz=0 THEN 8454016 "// vbhellgrün, &H80FF80
																	"  WHEN tkz<>0 AND gsz=0 AND (wdz<>0 or ahz<>0) THEN 14053594 "// vbhelllila, rgb(218,112,214)
																	"  WHEN tkz=0 AND gsz<>0 AND (wdz<>0 or ahz<>0) THEN 8438015 "// hellorange &H80C0FF
																	"  WHEN tkz<>0 AND gsz<>0 AND (wdz<>0 or ahz<>0) THEN 2139610 "// hellbraun RGB(218,165,32)
																	"  ELSE 16777215 "
																	" END wertsp "
																	"FROM (SELECT "
																	"SUM(art='gs' OR inhalt LIKE '%(gs)%') gsz"
																	",SUM(art='tk' OR inhalt LIKE '%(tk)%') tkz"
																	",SUM(art='wd' OR inhalt LIKE '%(wd)%') wdz"
																	",SUM(art='ah' OR inhalt LIKE '%(ah)%') ahz "
																	"FROM ( SELECT art,inhalt "
																	" FROM eintraege WHERE (art in ('tk','gs','wd','ah') OR inhalt RLIKE '\\((gs|tk|wd|ah)\\)') AND pat_id="+pid+
																	" ORDER BY zeitpunkt DESC LIMIT 7 "
																	") i) i",aktc,ZDB);
															if (!fb.obqueryfehler) {
																char ***eerg{0};
																while (eerg=fb.HolZeile(),eerg?*eerg:0) {
																	reine.hz("namsp",cjj(eerg,0));
																	reine.hz("wertsp",cjj(eerg,1));
																	break;
																}
															} // 										if (!fb.obqueryfehler)

															RS tm(My,"SELECT term"
																	", CASE "
																	"  WHEN TKZ<>0 AND GSZ=0 AND WDZ=0 and ahz=0 THEN 16767449 " // hellblau, &HFFD9D9
																	"  WHEN tkz=0 AND gsz<>0 AND wdz=0 and ahz=0 THEN 12648447 "// vbhellgelb, &HC0FFFF
																	"  WHEN tkz=0 AND gsz=0 AND ahz<>0 THEN 11195135 "// mittigahrosa, &HFFD2AA 
																	"  WHEN tkz=0 AND gsz=0 AND wdz<>0 THEN 12632319 "// mittigrosa, &HC0C0FF
																	"  WHEN tkz<>0 AND gsz<>0 AND wdz=0 and ahz=0 THEN 8454016 "// vbhellgrün, &H80FF80
																	"  WHEN tkz<>0 AND gsz=0 AND (wdz<>0 or ahz<>0) THEN 14053594 "// vbhelllila, rgb(218,112,214)
																	"  WHEN tkz=0 AND gsz<>0 AND (wdz<>0 or ahz<>0) THEN 8438015 "// hellorange &H80C0FF
																	"  WHEN tkz<>0 AND gsz<>0 AND (wdz<>0 or ahz<>0) THEN 2139610 "// hellbraun RGB(218,165,32)
																	"  ELSE 16777215 "
																	" END termsp "
																	"FROM (SELECT term "
																	",INSTR(term,' kot')<>0 tkz,INSTR(term,' sch')<>0 gsz,INSTR(term,' wag')<>0 wdz,INSTR(term,' ham')<>0 ahz "
																	"FROM (SELECT TRIM(GROUP_CONCAT(CONCAT(DATE_FORMAT(zp,'%d.%m.%y'),' ',LEFT(raum,3)) ORDER BY zp SEPARATOR '  ')) term "
																	"FROM termine t WHERE zp >= date(now()) AND pid = "+pid+") i) i",aktc,ZDB);
															if (!tm.obqueryfehler) {
																char ***terg{0};
																while (terg=tm.HolZeile(),terg?*terg:0) {
																	reine.hz("Termine",cjj(terg,0));
																	reine.hz("termsp",cjj(terg,1));
																	break;
																} // 											while (terg=tm.HolZeile(),terg?*terg:0)
															} // 										if (!tm.obqueryfehler)

															RS llb(My,"CALL geslabdp("+pid+",\"WHERE abkü='"+abkue+"' AND einheit='"+einh+"' "
																	"AND zeitpunkt<=STR_TO_DATE('"+erstl+"','%d.%m.%Y') GROUP BY zeitpunkt DESC LIMIT 3\")",aktc,ZDB);
															if (!llb.obqueryfehler) {
																char ***gerg{0};
																gerg=llb.HolZeile(); 
																gerg=llb.HolZeile(); if (gerg?*gerg:0) {
																	vorwert=atof(cjj(gerg,0));
																	reine.hz("Vorwert_1",string(cjj(gerg,0))+" ("+cjj(gerg,3)[8]+cjj(gerg,3)[9]+"."+
																			cjj(gerg,3)[5]+cjj(gerg,3)[6]+"."+cjj(gerg,3)[2]+cjj(gerg,3)[1]+")");
																} // 											gerg=llb.HolZeile(); if (gerg?*gerg:0)
																gerg=llb.HolZeile(); if (gerg?*gerg:0)
																	reine.hz("Vorwert_2",string(cjj(gerg,0))+" ("+cjj(gerg,3)[8]+cjj(gerg,3)[9]+"."+
																			cjj(gerg,3)[5]+cjj(gerg,3)[6]+"."+cjj(gerg,3)[2]+cjj(gerg,3)[1]+")");
															} // 										if (!llb.obqueryfehler)
														} else {
															reine.hz("namsp",16777215);
															reine.hz("wertsp",16777215);
														} // 									if (obpid) else
														const double iwert{atof(wert.c_str())};
														// 1. GFR
														if (iinstr(abkue,string("gfr"))!=-1 || iinstr(abkue,string("gfc"))!=-1 || iinstr(abkue,string("mdrd"))!=-1) {
															if (obpid) {
																RS mf(My,"SELECT COALESCE(("
																		" SELECT"
																		" IF(INSTR(lmp.medikament,'500')<>0,500,IF(INSTR(lmp.medikament,'850')<>0,850,IF(INSTR(lmp.medikament,'iquid'),200,1000)))*"
																		" (REPLACE(REPLACE(REPLACE(REPLACE(REPLACE(mo,',','.'),'½','.5'),'¼','.25'),'1/2','.5'),' ','')+"
																		" REPLACE(REPLACE(REPLACE(REPLACE(REPLACE(mi,',','.'),'½','.5'),'¼','.25'),'1/2','.5'),' ','')+"
																		" REPLACE(REPLACE(REPLACE(REPLACE(REPLACE(nm,',','.'),'½','.5'),'¼','.25'),'1/2','.5'),' ','')+"
																		" REPLACE(REPLACE(REPLACE(REPLACE(REPLACE(ab,',','.'),'½','.5'),'¼','.25'),'1/2','.5'),' ','')+"
																		" REPLACE(REPLACE(REPLACE(REPLACE(REPLACE(zn,',','.'),'½','.5'),'¼','.25'),'1/2','.5'),' ','')"
																		" ) summe"
																		" FROM lmp LEFT JOIN medarten ma ON ma.Medikament=lmp.medanfang"
																		" WHERE lmp.pat_id="+pid+" AND metf<>0"
																		" GROUP BY lmp.pat_id"
																		"),0) mfmg;",aktc,ZDB);
																if (!mf.obqueryfehler) {
																	char ***cerg{0};
																	while (cerg=mf.HolZeile(),cerg?*cerg:0) {
																		mfmg=cjj(cerg,0);
																		break;
																	}
																} // 										if (!mf.obqueryfehler)
																const long imf{atol(mfmg.c_str())};
																if ((iwert<30 && imf)||(iwert<45 && imf>1000)) {
																	hinw+="eGFR <-> "+mfmg+" mg Metformin/d!";
																	hinwsp=255; // vbred
																}
																if (iwert<45) {
																	if (ficd!="") ficd+=',';
																	if (iwert<15) ficd+="N18.5"; else if (iwert<30) ficd+="N18.4"; else ficd+="N18.3";
																	RS ni(My,"SELECT gicd FROM diagview WHERE pat_id = "+pid+" AND gicd RLIKE '^N1[89]' AND obdauer<>0",aktc,ZDB);
																	if (!ni.obqueryfehler) {
																		const char *const *const *const lerg{ni.HolZeile()};
																		if (lerg) {
																			if (ficdsp!=255) ficdsp=33023; // orange
																		} else {
//																			caus<<rot<<"neue Niereninsuffizienz!"<<endl;
																			ficdsp=255;
																		}
																	} // 	if (!ni.obqueryfehler)
																} // iwert < 45
															} // obpid
															// 2. nt-Pro-BNP
														} else if (abkue=="BNPS"||abkue=="NTBNPKO") {
															if (obpid && iwert>300) {
																if (ficd!="") ficd+=',';
																ficd+="I50.19";
																RS hi(My,"SELECT gicd FROM diagview WHERE pat_id = "+pid+" AND gicd RLIKE '^I50' AND obdauer<>0",aktc,ZDB);
																if (!hi.obqueryfehler) {
																	const char *const *const *const lerg{hi.HolZeile()};
																	if (lerg) {
																		if (ficdsp!=255) ficdsp=33023; // orange
																	} else {
//																		caus<<rot<<"neue Herzinsuffizienz!"<<endl;
																		ficdsp=255;
																	}
																} // 	if (!ni.obqueryfehler)
															} // if (obpid && iwert>300)
															// 3. CK
														} else if (iinstr(abkue,string("ck"))!=-1) {
															if (iwert>999) {
																hinw="CK hoch";
																hinwsp=255;
															}
															// 4. TSH
														} else if (iinstr(abkue,string("tsh"))!=-1 || iinstr(abkue,string("tsbf"))!=-1|| iinstr(abkue,string("tsbl"))!=-1) {
															if (iwert>(palter<25?2.5:palter>65?8:5)||iwert<0.25) {
																if (iwert<0.25) {
																	hinw="V.a. zu viel SD-Hormon";
																	hinwsp=255;
																} else {
																	hinw="mögl.unzur.SD-Substitution";
																	hinwsp=255;
																} // if (iwert<0.25)
																if (obpid) {
																	RS llb(My,"CALL geslabdp("+pid+",\"WHERE abkü='fT4' AND zeitpunkt>now()-INTERVAL 5 DAY GROUP BY zeitpunkt DESC LIMIT 1\")",aktc,ZDB);
																	char ***gerg{0};
																	if (!llb.obqueryfehler) {
																		gerg=llb.HolZeile();
																		if (gerg?*gerg:0) {
																			hinw+=" (";
																			hinw+=cjj(gerg,1); // fT4
																			hinw+=" ";
																			hinw+=cjj(gerg,0); // (wert)
																			hinw+=" ";
																			hinw+=cjj(gerg,2); // pmol/l
																			hinw+=" ";
																			hinw+=cjj(gerg,3)[8]; // 2021-04-29
																			hinw+=cjj(gerg,3)[9]; // 2021-04-29
																			hinw+='.';
																			hinw+=cjj(gerg,3)[5]; // 2021-04-29
																			hinw+=cjj(gerg,3)[6]; // 2021-04-29
																			hinw+='.';
																			hinw+=")";
																		} // 													if (gerg?*gerg:0)
																	} // 												if (!llb.obqueryfehler)
																} // 											if (obpid)
															} // 										if (iwert>(palter<25?2.5:palter>65?8:5)||iwert<0.25)
															// 5. fT4
														} else if (iinstr(abkue,string("ft4"))!=-1) {
															if (iwert<12||iwert>22) {
																if (iwert>22) {
																	hinw="V.a. zu viel SD-Hormon";
																	hinwsp=255;
																} else {
																	hinw="V.a. zu wenig SD-Hormon";
																	hinwsp=255;
																}
																if (obpid) {
																	RS llb(My,"CALL geslabdp("+pid+",\"WHERE abkü IN ('TSH','TSBF','TSBL') AND zeitpunkt>now()-INTERVAL 5 DAY GROUP BY zeitpunkt DESC LIMIT 1\")",aktc,ZDB);
																	char ***gerg{0};
																	if (!llb.obqueryfehler) {
																		gerg=llb.HolZeile();
																		if (gerg?*gerg:0) {
																			hinw+=" (TSH "; // cjj(gerg,1); // TSH
																			hinw+=cjj(gerg,0); // (wert)
																			hinw+=" ";
																			hinw+=cjj(gerg,2); // IU/ml
																			hinw+=" ";
																			hinw+=cjj(gerg,3)[8]; // 2021-04-29
																			hinw+=cjj(gerg,3)[9]; // 2021-04-29
																			hinw+='.';
																			hinw+=cjj(gerg,3)[5]; // 2021-04-29
																			hinw+=cjj(gerg,3)[6]; // 2021-04-29
																			hinw+='.';
																			hinw+=")";
																		} // 													if (gerg?*gerg:0)
																	} // 												if (!llb.obqueryfehler)
																} // 											if (obpid)
															} // 										if (iwert<12||iwert>22)
																// SELECT abkü from laborparameter WHERE langtext IN  ('Kalium','Kalium im Heparinblut');
															// 6. Kalium
														} else if (abkue=="k"||abkue=="K"||abkue=="KALI"||abkue=="KHEP"||abkue=="TM<>K<>Labor2"||
																abkue=="TM<>KALI<>Labor Schottdorf"||abkue=="TM<>K<>"||abkue=="TM<>K<>Labor1") {
															if (iwert<3.5 ||iwert>5.5) {
																hinw="V.a. Dyskaliämie";
																hinwsp=255;
															}
															// 7. Hämoglobin
														} else if (abkue=="HB") {
															const int obm{strcmp(cjj(ferg,3),"w")};
															if (vorwert!=0 && vorwert-iwert>1.5) {
																hinw="Hb-Abfall!";
																hinwsp=255;
															} else if ((obm&&iwert<13.5)||iwert<11.5) {
																hinw="V.a. Anämie";
																if (obpid) {
																	if (ficd!="") ficd+=',';
																	ficd+="D64.9";
																	// RS an(My,"SELECT icd FROM `diagnosen` WHERE pat_id = "+pid+" AND diagtext LIKE '%anämie%' "
																	// "AND diagsicherheit NOT IN ('A','Z') AND COALESCE(f6010,0)=0 AND obdauer<>0",aktc,ZDB);
																	RS an(My,"SELECT icd FROM diagview WHERE pat_id="+pid+" AND gicd RLIKE '^D46|^D5[012678]|^D6[14]' AND obdauer<>0",aktc,ZDB);
																	if (!an.obqueryfehler) {
																		const char *const *const *const lerg{an.HolZeile()};
																		if (lerg) {
																			if (ficdsp!=255) ficdsp=33023; // orange
																			hinwsp=33023; // orange
																		} else {
//																			caus<<rot<<"neue Anämie!"<<endl;
																			ficdsp=255;
																			hinwsp=255;
																		}
																	} // 	if (!ni.obqueryfehler)
																} // if (obpid)
															} //										if (vorwert!=0 && vorwert-iwert>1.5)    else if
															// 8. Harnsäure
														} else if (abkue=="HS") {
															if (iwert>7) {
																	if (ficd!="") ficd+=',';
																	ficd+="E79.0";
																	RS hs(My,"SELECT icd FROM diagview WHERE pat_id="+pid+" AND gicd RLIKE '^E79.0' AND obdauer<>0",aktc,ZDB);
																	if (!hs.obqueryfehler) {
																		const char *const *const *const lerg{hs.HolZeile()};
																		if (lerg) {
																			if (ficdsp!=255) ficdsp=33023; // orange
																		} else {
																			ficdsp=255;
																		}
																	} // 	if (!ni.obqueryfehler)
															}
															// 9. Cholesterin
														} else if (abkue=="LDLB"||abkue=="LDLMG"||abkue=="LDLH01"||abkue=="LDL") {
															const int obs{strcmp(cjj(ferg,5),"0")};
															if (!obs && iwert>140) {
																	if (ficd!="") ficd+=',';
																	ficd+="E78.0";
																	RS hs(My,"SELECT icd FROM diagview WHERE pat_id="+pid+" AND gicd RLIKE '^E78' AND obdauer<>0",aktc,ZDB);
																	if (!hs.obqueryfehler) {
																		const char *const *const *const lerg{hs.HolZeile()};
																		if (lerg) {
																			if (ficdsp!=255) ficdsp=33023; // orange
																		} else {
																			ficdsp=255;
																		}
																	} // 	if (!ni.obqueryfehler)
															}
														} // if (abkue==  ...			else if (abkue=="HB")
															//									if (hinw!="") KLA
														reine.hz("Hinweise",hinw);
														reine.hz("hinwsp",hinwsp);
//														if (ficd!="") caus<<"fICD: "<<ficd<<endl;
														reine.hz("fICD",ficd);
														reine.hz("fICDsp",ficdsp);
														//									KLZ
														reine.schreib(/*sammeln*/0,/*obverb*/obverb,/*idp*/0);
														goto fertig;
													} // 											if (1)
												} // 														if (!(ferg?*ferg:0)) else
											} // 								if (!pd.obqueryfehler)
naeiru:;
										} // 									for(unsigned aru=0;aru<2;aru++)
									} // for (iru=0;iru<4;
fertig:;
								} // 							if (!obanf) else if else
							} // 						while(getasciiline(mdat,zeile))

							RS ftg(My,"UPDATE `"+labpatel+"` SET fertig=1 WHERE id="+datid,aktc,ZDB);
						} // 					if (mdat.is_open())
					} // if (dgibts)
				} // 				if (!(cerg=nachschau.HolZeile())||!*cerg)
			} // 			if (!nachschau.obqueryfehler)
		} // 		for(size_t i=0;i<lrue.size();i++)
	} // 		else if (!loeschalle && !loeschunvollst && umben.empty())
	fLog(blaus+Tx[T_fertig]+schwarz,obverb,oblog);
	ZDB=altZDB;
} // void hhcl::pvirtfuehraus  //α

// wird aufgerufen in lauf
void hhcl::virtschlussanzeige()
{   //ω
	dhcl::virtschlussanzeige(); //α
} // void hhcl::virtschlussanzeige

// wird aufgerufen in: main
void hhcl::virtautokonfschreib()
{
	// int altobverb=obverb;
	// obverb=1;
	hLog(violetts+Txk[T_autokonfschreib]+schwarz+", "+Txk[T_zu_schreiben]+((rzf||hccd.obzuschreib)?Txk[T_ja]:Txk[T_nein]));
	/*//
		capizukonf und hylazukonf hier immer 0
		char buf[200];
		sprintf(buf,"rzf: %d, capizukonf: %d, hylazukonf: %d, obkschreib: %d",(int)rzf, (int)capizukonf, (int)hylazukonf, (int)obkschreib);
		hLog(blaus+buf+schwarz);
	 */
	struct stat kstat={0};
	if (lstat(akonfdt.c_str(),&kstat))
		hccd.obzuschreib=1;
	if (rzf||hccd.obzuschreib) {
		hLog(gruens+Tx[T_schreibe_Konfiguration]+schwarz,/*oberr*/obverb);
		// restliche Erklaerungen festlegen
		////    agcnfA.setzbem("language",sprachstr);
		hcl::virtautokonfschreib(); //ω
	} // if (rzf||obkschreib) //α
	// obverb=altobverb;
} // void hhcl::virtautokonfschreib

hhcl::~hhcl() 
{ //ω
} //α

void hhcl::virtlieskonfein()
{
	const int altobverb{obverb};
	//	obverb=1;
	hLog(violetts+Txk[T_virtlieskonfein]+schwarz);
	//nachclvors=vorsl;
	hcl::virtlieskonfein(); //ω
	hLog(violetts+Txk[T_Ende]+Txk[T_virtlieskonfein]+schwarz); //α
	obverb=altobverb;
} // void hhcl::virtlieskonfein()

int main(int argc,char** argv)
{
	if (argc>1) { //ω
	} //α
	hhcl hhi(argc,argv); // hiesige Hauptinstanz, mit lngzuw, setzlog und pruefplatte
	hhi.lauf(); // Einleitungsteil mit virtuellen Funktionen, 
	// mit virtVorgbAllg,pvirtVorgbSpeziell,initopt,parsecl,pvirtmacherkl,zeighilfe,virtlieskonfein,verarbeitkonf,lieszaehlerein,MusterVorgb,dovi,dovs,virtzeigversion
	// virtautokonfschreib,update,
	return hhi.retu;
} // int main 

void hhcl::virttesterg()
{
} //ω
