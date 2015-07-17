// $Id: nobUsual.h 9357 2014-04-25 15:35:25Z FloSoft $
//
// Copyright (c) 2005 - 2011 Settlers Freaks (sf-team at siedler25.org)
//
// This file is part of Return To The Roots.
//
// Return To The Roots is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Return To The Roots is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Return To The Roots. If not, see <http://www.gnu.org/licenses/>.

#ifndef NOB_USUAL_H_
#define NOB_USUAL_H_

#include "noBuilding.h"
#include "EventManager.h"

class Ware;
class nofBuildingWorker;

// Gew�hnliches Geb�ude mit einem Arbeiter und Waren
class nobUsual : public noBuilding
{
        /// Der Typ, der hier arbeitet
        nofBuildingWorker* worker;
        /// Produktivit�t
        unsigned short productivity;
        /// Produktion eingestellt? (letzteres nur visuell, um Netzwerk-Latenzen zu verstecken)
        bool disable_production, disable_production_virtual;
        /// Warentyp, den er zuletzt bestellt hatte (bei >1 Waren)
        unsigned char last_ordered_ware;
        /// Rohstoffe, die zur Produktion ben�tigt werden
        unsigned char wares[3];
        /// Bestellte Waren
        list<Ware*> * ordered_wares;
        /// Bestell-Ware-Event
        EventManager::EventPointer orderware_ev;
        /// Rechne-Produktivit�t-aus-Event
        EventManager::EventPointer productivity_ev;
        /// Letzte Produktivit�ten (Durschnitt = Gesamtproduktivit�t), vorne das neuste !
        static const unsigned LAST_PRODUCTIVITIES_COUNT = 6;
        unsigned short last_productivities[LAST_PRODUCTIVITIES_COUNT];

protected:
        friend class SerializedGameData;
        friend class BuildingFactory;
        nobUsual(const BuildingType type, const unsigned short x, const unsigned short y, const unsigned char player, const Nation nation);
        nobUsual(SerializedGameData* sgd, const unsigned obj_id);
    public:

        /// Wird gerade gearbeitet oder nicht?
        bool is_working;

        ~nobUsual();

        /// Aufr�ummethoden
    protected:  void Destroy_nobUsual();
    public:     void Destroy() { Destroy_nobUsual(); }

        /// Serialisierungsfunktionen
    protected: void Serialize_nobUsual(SerializedGameData* sgd) const;
    public: void Serialize(SerializedGameData* sgd) const { Serialize_nobUsual(sgd); }

        virtual GO_Type GetGOT() const { return GOT_NOB_USUAL; }

        void Draw(int x, int y);

        bool HasWorker() const;

        /// Event-Handler
        void HandleEvent(const unsigned int id);
        /// Legt eine Ware am Objekt ab (an allen Stra�enknoten (Geb�ude, Baustellen und Flaggen) kann man Waren ablegen
        void AddWare(Ware* ware);
        /// Wird aufgerufen, wenn von der Fahne vor dem Geb�ude ein Rohstoff aufgenommen wurde
        bool FreePlaceAtFlag();
        /// Eine bestellte Ware konnte doch nicht kommen
        void WareLost(Ware* ware);
        /// Wird aufgerufen, wenn ein Arbeiter f�r das Geb�ude gefunden werden konnte
        void GotWorker(Job job, noFigure* worker);
        /// Wird vom Arbeiter aufgerufen, wenn er im Geb�ude angekommen ist
        void WorkerArrived();
        /// Wird vom Arbeiter aufgerufen, wenn er nicht (mehr) zur Arbeit kommen kann
        void WorkerLost();

        /// Gibt den Warenbestand (eingehende Waren - Rohstoffe) zur�ck
        unsigned char GetWares(const unsigned int id) const { return wares[id]; }
        /// Pr�ft, ob Waren f�r einen Arbeitsschritt vorhanden sind
        bool WaresAvailable();
        /// Verbraucht Waren
        void ConsumeWares();

        /// Berechnet Punktewertung f�r Ware type, start ist der Produzent, von dem die Ware kommt
        unsigned CalcDistributionPoints(noRoadNode* start, const GoodType type);

        /// Wird aufgerufen, wenn eine neue Ware zum dem Geb�ude geliefert wird (nicht wenn sie bestellt wurde vom Geb�ude!)
        void TakeWare(Ware* ware);

        /// Bestellte Waren
        inline unsigned AreThereAnyOrderedWares() {return ordered_wares->size();}

        /// Gibt Pointer auf Produktivit�t zur�ck
        const unsigned short* GetProduktivityPointer() const { return &productivity; }

        /// Ermittelt, ob es sich bei diesem Geb�ude um ein Bergwerk handelt
        bool IsMine() const { return type >= BLD_GRANITEMINE && type <= BLD_GOLDMINE; }

        /// Stoppt/Erlaubt Produktion (visuell)
        void StopProductionVirtual() { disable_production_virtual = !disable_production_virtual; }
        /// Stoppt/Erlaubt Produktion (real)
        void StopProduction();
        /// Fragt ab, ob Produktion ausgeschaltet ist (visuell)
        bool IsProductionDisabledVirtual() { return disable_production_virtual; }
        /// Fragt ab, ob Produktion ausgeschaltet ist (real)
        bool IsProductionDisabled() { return disable_production; }
        /// Setzt Produktivit�t instant auf 0 (Keine Ressourcen mehr)
        void SetProductivityToZero();

};


#endif
