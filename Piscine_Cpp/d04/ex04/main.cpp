// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 02:38:18 by gbourgeo          #+#    #+#             //
//   Updated: 2018/07/06 03:10:15 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "MiningBarge.hpp"
#include "DeepCoreMiner.hpp"
#include "StripMiner.hpp"
#include "AsteroKreog.hpp"
#include "KoalaSteroid.hpp"

int main()
{
	MiningBarge		*barge = new MiningBarge;

	barge->equip(0);
	barge->mine(0);

	barge->equip(new DeepCoreMiner);
	barge->mine(0);
	AsteroBocal		*a = new AsteroBocal;
	barge->mine(a);
	BocalSteroid	*b = new BocalSteroid;
	barge->mine(b);

	barge->equip(new StripMiner);
	barge->mine(a);
	barge->mine(b);

	barge->equip(new StripMiner);
	barge->mine(a);
	barge->mine(b);

	barge->equip(new DeepCoreMiner);
	barge->mine(a);
	barge->mine(b);

	delete a;
	delete b;
	delete barge;
	return 0;
}
