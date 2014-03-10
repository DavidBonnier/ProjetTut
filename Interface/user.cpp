///////////////////////////////////////////////////////////////////////////
//! \file user.cpp
//!
//! \brief Mise en place de toutes les fonctionnalités relatives à la gestion des Utilisateurs
//!
//! On va stocker dans un fichier xml nommé "Utilisateurs.xml" les différents utilisateurs créé. A la première utilisation (stocké sous forme de booléen dans le .xml décrit ci-avant), l'utilisateur doit s'enregistrer. Par la suite, il lui sera possible d'accéder au logiciel sans s'être connecté. Si toutefois il souhaite que ses paramètres soient chargés, il devra se connecter.
//! \date 01/02/2014
//! \version 4.2
/////////////////////////////////////////////////////////////////////////// s

#include "user.h"

User::User(QDialog *parent)
    : QDialog(parent)
{
    user_actuel_IsAdmin = false;
	premUtil = false;
}

///////////////////////////////////////////////////////////////////////////
//! \author ROCHE Hugo
//! \date 31/01/2014
//!
//! \throw Indentifiant invalide, mot de passe ne correspondant pas à l'identifiant.
//!
//! L'utilisateur saisi son identifiant et son mot de passe. Par la suite on parcours notre document .xml (en utilisant le sytème d'arbre présent). Si l'identifiant et le mot de passe concorde, la connexion est un succès. Dans les autres cas, on affiche une QMessageBox d'erreur.
///////////////////////////////////////////////////////////////////////////
void User::Connexion()
{
    bool ok_id, ok_mdp;
    QString id, mdp;
    QDomDocument dom;
    id = QInputDialog::getText(this, tr("Gestion des utilisateurs "),
                tr("Identifiant : "), QLineEdit::Normal, QString(), &ok_id);
    if (ok_id && !id.isEmpty())
    {
        mdp = QInputDialog::getText(this, tr("Gestion des utilisateurs "),
                tr("Mot de passe : "), QLineEdit::Password, QString(), &ok_mdp);
        if(!mdp.isEmpty() && ok_mdp)
        {
            QFile file("Utilisateurs.xml");
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
            dom.setContent(&file);
            QDomElement root=dom.documentElement();
            QDomElement child=root.firstChild().toElement();
            while(!child.isNull())
            {
                QDomElement grandChild=child.firstChild().toElement();
                if(child.tagName() == "utilisateur")
                {
                    while(!grandChild.isNull())
                    {
                        if (grandChild.tagName() == "identifiant")
                        {
                            if(grandChild.text() == id)
                            {
                                grandChild = grandChild.nextSibling().toElement();
                                if (grandChild.text() == mdp)
                                {
                                    id_user_actuel = id;
                                    mdp_user_actuel = mdp;
                                    grandChild = grandChild.nextSibling().toElement();
                                    if(grandChild.text() == "true")
                                        user_actuel_IsAdmin = true;
                                    else
                                        user_actuel_IsAdmin = false;
                                    QMessageBox* success = new QMessageBox(QMessageBox::NoIcon, "Gestion des utilisateurs", "Bienvenue, " + id);
                                    success->setIconPixmap(QPixmap(":/Interface/Resources/validationConnexion.png"));
                                    success->show();
                                    file.close();
                                    return;
                                }
                                else
                                {
                                    QMessageBox* password_error = new QMessageBox(QMessageBox::NoIcon, "Gestion des utilisateurs", "Mot de passe invalide !");
                                    password_error->setIconPixmap(QPixmap(":/Interface/Resources/erreurConnexion.png"));
                                    password_error->show();
                                    if(password_error->exec() == QMessageBox::Ok)
                                    {
                                        file.close();
                                        Connexion();
                                        return;
                                    }
                                    else
                                    {
                                        return;
                                        file.close();
                                    }
                                }
                            }
                        }
                        grandChild = grandChild.nextSibling().toElement();
                    }
                }
                child = child.nextSibling().toElement();
            }
            QMessageBox* id_error = new QMessageBox(QMessageBox::NoIcon, "Gestion des utilisateurs", "Identifiant invalide !");
            id_error->setIconPixmap(QPixmap(":/Interface/Resources/erreurConnexion.png"));
            id_error->show();
            if(id_error->exec() == QMessageBox::Ok)
            {
                Connexion();
                return;
            }
            else
            {
                file.close();
                return;
            }

        }
    }
}

///////////////////////////////////////////////////////////////////////////
//! \author ROCHE Hugo
//! \date 31/01/2014
//!
//! \throw Identifiant déjà utilisé, données saisies invalides (pour l'administrateur) ou utilisateur non administrateur.
//!
//! Fonction accessible que si l'utilisateur connecté est administrateur (booléen user_actuel_IsAdmin) ou si c'est la première utilisation du logiciel. Premier parcours du .xml pour vérifier l'existence de l'idenifiant (éviter les doublons). Si ce parcours est un succès, alors on utilise un QTextStream pour remplacer la dernière ligne du fichier par les informations de l'utilisateur créé.
///////////////////////////////////////////////////////////////////////////
void User::Enregistrement()
{
    if(premUtil || user_actuel_IsAdmin)
    {
        bool ok_id, ok_mdp, ok_admin;
        QString id, mdp, admin, temp;
        id = QInputDialog::getText(this, tr("Gestion des utilisateurs "),
                    tr("Identifiant : "), QLineEdit::Normal, QString(), &ok_id);
        if (ok_id && !id.isEmpty())
        {
            QFile file("Utilisateurs.xml");
            if (!file.open(QIODevice::ReadOnly))
                return;
            QTextStream flux(&file);
            //on va d'abord vérifier si l'utilisateur existe déjà (pas 2 fois le même identifiant)
            while(!flux.atEnd())
            {
                QString ligne = flux.readLine();
                if(ligne.contains(id))
                {
                    QMessageBox* user_exists = new QMessageBox(QMessageBox::NoIcon, "Gestion des utilisateurs", "Identifiant déjà utilisé !");
                    user_exists->setIconPixmap(QPixmap(":/Interface/Resources/erreurConnexion.png"));
                    user_exists->show();
                    return;
                }
            }
            mdp = QInputDialog::getText(this, tr("Gestion des utilisateurs "),
                tr("Mot de passe : "), QLineEdit::Password, QString(), &ok_mdp);
            if(!mdp.isEmpty() && ok_mdp)
            {
				if(!premUtil)
				{
					 admin = QInputDialog::getText(this, tr("Gestion des utilisateurs "),
						tr("Administrateur(O/N) : "), QLineEdit::Normal, QString(), &ok_admin);

					if(!admin.isEmpty() && ok_admin)
					{
						if (admin == "O" || admin == "o")
							admin = "true";
						else if (admin == "N" || admin == "n")
							admin = "false";
						else
						{
							QMessageBox* invalid_data = new QMessageBox(QMessageBox::NoIcon, "Gestion des utilisateurs", "Données saisies invalides ! ");
                            invalid_data->setIconPixmap(QPixmap(":/Interface/Resources/erreurConnexion.png"));
							invalid_data->show();
							if(invalid_data->exec() == QMessageBox::Ok)
							{
								Enregistrement();
								file.close();
								return;
							}
							else
							{
								file.close();
								return;
							}
						}
					}
				}
				else
					admin = "true";
				
				file.close();
                QFile tempFile("Utilisateurs.xml");
                if(!tempFile.open(QIODevice::ReadWrite))
                    return;
                QTextStream in(&tempFile);
                QString ligne_a_rajouter = "<utilisateur> \n <identifiant>" + id + "</identifiant> \n <password>" + mdp + "</password> \n <admin> " + admin + "</admin> \n </utilisateur> \n </utilisateurs>";
                while (!in.atEnd())
                {
                    QString ligne = in.readLine();
                    if(ligne.contains("</utilisateurs>"))
                    {
                        temp.append(ligne_a_rajouter);
                        break;
                    }
                    else
                    {
                        temp.append(ligne + "\n");
                    }
                }
                tempFile.resize(0);
                in << temp;
                tempFile.close();
                QMessageBox* success = new QMessageBox(QMessageBox::NoIcon, "Gestion des utilisateurs", "Utilisateur créé avec succès.");
                success->setIconPixmap(QPixmap(":/Interface/Resources/validationConnexion.png"));
                success->show();
            }
        }
        else
        {
            return;
        }
    }

    else if (!user_actuel_IsAdmin)
    {
        QMessageBox* notAdmin = new QMessageBox(QMessageBox::NoIcon, "Gestion des utilisateurs", "Vous devez disposer de droits d'administrateur pour effectuer cette action.");
        notAdmin->setIconPixmap(QPixmap(":/Interface/Resources/erreurConnexion.png"));
        notAdmin->show();
        return;
    }
}

///////////////////////////////////////////////////////////////////////////
//! \author ROCHE Hugo
//! \date 31/01/2014
//!
//! \throw Identifiant inexistant ou utilisateur non administrateur.
//!
//! L'utilisateur (connecté en tant qu'administrateur) saisi l'identifiant de l'utilisateur à supprimer. On parcours notre fichier (parser DOM) et si l'utilisateur est trouvé, alors on passe la valeur booléenne user_exists à true et on supprime l'enfant concerné (removeChild).Si à la fin du fichier, user_exists est à false, l'identifiant n'existe pas. On affiche donc une QMessageBox d'erreur.
///////////////////////////////////////////////////////////////////////////
void User::RemoveUtil()
{
    if(user_actuel_IsAdmin)
    {
        bool ok_id, id_exists = false;
        QString id;
        QDomDocument dom;
        id = QInputDialog::getText(this, tr("Gestion des utilisateurs "),
                    tr("Saisissez l'identifiant de l'utilisateur à supprimer: "), QLineEdit::Normal, QString(), &ok_id);
        if (ok_id && !id.isEmpty())
        {
            QFile file("Utilisateurs.xml");
            if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
                return;
            dom.setContent(&file);
            QDomElement root=dom.documentElement();
            QDomElement child=root.firstChild().toElement();
            QTextStream in (&file);
            while(!child.isNull())
            {
                QDomElement grandChild = child.firstChild().toElement();
                while(!grandChild.isNull())
                {
                    QString test = grandChild.text();
                    if(grandChild.tagName() == "identifiant")
                    {
                        if(grandChild.text() == id)
                        {
                            root.removeChild(child);
                            id_exists = true;
                        }
                    }
                    grandChild = grandChild.nextSibling().toElement();
                }
                child = child.nextSibling().toElement();
            }
            if(!id_exists)
            {
                QMessageBox* id_error = new QMessageBox(QMessageBox::NoIcon, "Gestion des utilisateurs", "Identifiant invalide !");
                id_error->setIconPixmap(QPixmap(":/Interface/Resources/erreurConnexion.png"));
                id_error->show();
                if(id_error->exec() == QMessageBox::Ok)
                {
                    RemoveUtil();
                    file.close();
                    return;
                }
                else
                {
                    file.close();
                    return;
                }

            }
            QMessageBox* success = new QMessageBox(QMessageBox::NoIcon, "Gestion des utilisateurs", "L'utilisateur " + id + " a bien été supprimé.");
            success->setIconPixmap(QPixmap(":/Interface/Resources/validationConnexion.png"));
            success->show();

            file.close();
            file.open(QIODevice::WriteOnly);
            QTextStream out( &file );
            out << dom.toString();
            file.close();
        }
    }

    else
    {
        QMessageBox* notAdmin = new QMessageBox(QMessageBox::NoIcon, "Gestion des utilisateurs", "Vous devez disposer de droits d'administrateur pour effectuer cette action.");
        notAdmin->setIconPixmap(QPixmap(":/Interface/Resources/erreurConnexion.png"));
        notAdmin->show();
        return;
    }
}

///////////////////////////////////////////////////////////////////////////
//! \author ROCHE Hugo
//! \date 31/01/2014
//!
//! \return true si c'est la première utilisation, false dans le cas contraire.
//! On regarde la valeur contenue dans la balise <firstUse> présente dans le fichier xml. Si cette valeur est à true, alors on retourne "true" et on passe la valeur à false. Dans le cas contraire, ce n'est pas la première utilisation du logiciel on retourne false. Cette fonction est utilisée dans Enregistrement() et dans le main.
///////////////////////////////////////////////////////////////////////////
bool User::firstUse()
{
    bool tempBool = false;
    QDomDocument dom;
    QFile file("Utilisateurs.xml");
    if (!file.open(QIODevice::ReadWrite))// | QIODevice::Text))
        return false;

    //on va vérifier sur Utilisateurs.xml si c'est la première utilisation
    QString temp;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString ligne = in.readLine();
        if (ligne.contains("firstUse") && ligne.contains("true"))
        {
            temp.append("<firstUse>false</firstUse>\n");
            tempBool = true;
        }
        else
        {
            temp.append(ligne + "\n");
        }
    }
    file.resize(0);
    in << temp;
    file.close();
    return tempBool;
}

