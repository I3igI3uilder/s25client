// Copyright (C) 2005 - 2021 Settlers Freaks (sf-team at siedler25.org)
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "MusicPlayer.h"
#include "Loader.h"
#include "drivers/AudioDriverWrapper.h"
#include "ogl/MusicItem.h"
#include "libsiedler2/Archiv.h"
#include "libsiedler2/ArchivItem.h"
#include "libsiedler2/ErrorCodes.h"
#include "libsiedler2/prototypen.h"
#include "s25util/Log.h"
#include "s25util/StringConversion.h"

MusicPlayer::MusicPlayer() : playing(false) {}

/**
 *  Startet Abspielvorgang
 */
void MusicPlayer::Play()
{
    playing = true;
    PlayNext();
}

/**
 *  Stoppt Abspielvorgang
 */
void MusicPlayer::Stop()
{
    AUDIODRIVER.StopMusic();
    playing = false;
}

/**
 * Spielt nächstes Stück ab
 */
void MusicPlayer::PlayNext()
{
    std::string song = list.getNextSong();

    // Am Ende der Liste angekommen?
    if(song.empty())
    {
        Stop();
        return;
    }

    // Evtl ein Siedlerstück ("sNN")?
    if(song.length() == 3 && song[0] == 's')
    {
        unsigned nr = s25util::fromStringClassicDef(song.substr(1), 999u);
        if(nr > 0 && nr <= LOADER.sng_lst.size())
            LOADER.sng_lst[nr - 1]->Play();
        return;
    }

    // anderes benutzerdefiniertes Stück abspielen
    // in "sng" speichern, daher evtl. altes Stück erstmal löschen
    sng.clear();

    LOG.write(_("Loading \"%1%\": ")) % song;

    // Neues Stück laden
    if(int ec = libsiedler2::loader::LoadSND(song, sng))
    {
        LOG.write(_("Error: %1%\n")) % libsiedler2::getErrorString(ec);
        Stop();
        return;
    }
    LOG.write(_("OK\n"));

    // Und abspielen
    auto* curSong = dynamic_cast<MusicItem*>(sng[0]);
    if(curSong)
        curSong->Play();
}
