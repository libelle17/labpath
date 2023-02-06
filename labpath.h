#define DPROG "labpath"
// fuer verschiedene Sprachen //α
enum T_      
{
	T_virtVorgbAllg,
	T_pvirtVorgbSpeziell,
	T_virtMusterVorgb,
	T_pvirtvorrueckfragen,
	T_virtrueckfragen,
	T_Fehler_beim_Pruefen_von,
	T_Fuege_ein, //ω
	T_eindeutige_Identifikation,
	T_Laborparameter,
	T_LWert,
	T_Einheit,
	T_Vorwert_1,
	T_Vorwert_2,
	T_Normbereich,
	T_HinweisedL,
	T_Hinweise,
	T_fehlende_ICDs,
	T_Termine,
	T_Laborwert,
	T_quellvz,
	T_pruefdb_k,
	T_pruefdb_l,
	T_initialisiert_nur_die_Tabellen,
	T_Einlesedatum,
	T_Pfad,
	T_Name,
	T_Groesse,
	T_Aenderungsdatum,
	T_dfertig,
	T_Path_Labor_Einlesungen,
	T_qvz_k,
	T_qvz_l,
	T_Verzeichnis_der_Quelldateien,
	T_Verzeichnis_der_einzulesenden_Dateien,
	T_prueflpath,
	T_prueflpatel,
	T_ID_der_Einlesung,
	T_fertig,
	T_Dateien_gefunden,
	T_davon_neu,
	T_Parse,
	T_Patient,
	T_namsp,
	T_wertsp,
	T_hinwsp,
	T_termsp,
	T_ficdsp,
	T_MAX //α
}; // enum T_ //ω
//α
class hhcl:public dhcl
{
	private: //ω
	 string labpatel;
	 string labpath;
	protected: //α //ω
		uchar nurpruefdb=0;
		string quellvz; // Verzeichnis der einzulesenden Dateien
	public: //α //ω
	private: //α //ω
		void tabnamen();
		void prueftbl();
		void prueflpath(DB *My, const size_t aktc, const int obverb, const int oblog, const uchar direkt=0);
		void prueflpatel(DB *My, const size_t aktc, const int obverb, const int oblog, const uchar direkt=0);
		void virttesterg(); //α
		void virtlieskonfein();
		void virtautokonfschreib();
		int vverarbeit(const string& datei); // Vergleichsdatei verarbeiten
		void usschluss(const size_t aktc);
	protected: 
		// void virtlgnzuw(); // wird aufgerufen in: virtrueckfragen, parsecl, lieskonfein, hcl::hcl nach holsystemsprache
		void virtVorgbAllg();
		void pvirtVorgbSpeziell()
#ifdef VOMHAUPTCODE
			__attribute__((weak)) // implementationsspezifische Vorgaben, Modul vgb.cpp)
#endif
			;
		/*
		void pruefPatID(const int aktc,insv& rus)
#ifdef VOMHAUPTCODE
			__attribute__((weak)) // implementationsspezifische Adresspruefung)
#endif
			;
		*/
		void fuellpql();
		/*
		void auswertpql(const size_t i,insv& rus)
#ifdef VOMHAUPTCODE
			__attribute__((weak)) // implementationsspezifische Adresspruefung)
#endif
			;
		*/
		void ergpql()
#ifdef VOMHAUPTCODE
			__attribute__((weak)) // implementationsspezifische Adresspruefung)
#endif
			;
		void usmod(const size_t aktc,svec *zlangtp=0,svec *zabkp=0, svec *zwertep=0,svec *zverfap=0,tm *eingtmp=0)
#ifdef VOMHAUPTCODE
			__attribute__((weak)) // implementationsspezifische Adresspruefung)
#endif
			;
		void vordverarb(const size_t aktc)
#ifdef VOMHAUPTCODE
			__attribute__((weak)) // implementationsspezifische Adresspruefung)
#endif
			;
		void nachbearbeit(const size_t aktc,const uchar obusmod/*=0*/)
#ifdef VOMHAUPTCODE
			__attribute__((weak)) // implementationsspezifische Adresspruefung)
#endif
			;
		void russchreib(insv &rus,const int aktc,string *usidp);
		void virtinitopt(); // (programm-)spezifische Optionen
		void pvirtmacherkl();
		void virtMusterVorgb();
		void pvirtvorzaehler();
		void virtzeigversion(const string& ltiffv=nix);
		void pvirtvorrueckfragen();
		void pvirtnachrueckfragen();
		void virtpruefweiteres();
		void virtzeigueberschrift();
		void pvirtfuehraus();
		void virtschlussanzeige(); //ω
	public: //α
		hhcl(const int argc, const char *const *const argv);
		~hhcl();
}; // class hhcl //ω
