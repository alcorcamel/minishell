/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 11:57:00 by demane            #+#    #+#             */
/*   Updated: 2026/01/09 17:53:19 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
(en bonus)
fait une premier passage sur la liste pour checker si && et/ou ||

pas de pipe au debut
pas de pipe a la fin
pas de redirs qui se suivent

apres un pipe / redir: word

si plusieurs redir cmd > a.txt > b.txt > c.txt
(la sortie est faite ds le dernier fichier mais les intermediaires sont qd mm crees)
avt un > obligatoirement une cmd


*/
