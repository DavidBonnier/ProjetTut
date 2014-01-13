#include "user.h"

User::User(QDialog *parent)
	: QDialog(parent)
{
}

User::~User()
{

}

// Connexion
void User::Connexion()
{
	bool ok_id, ok_mdp;
	QString id, mdp;
	QString ligne;
	QStringList info;
	QFile file("Utilisateurs.txt");

	id = QInputDialog::getText(this, tr("Connexion "),
				tr("Identifiant : "), QLineEdit::Normal, QString(), &ok_id);
	if (ok_id && !id.isEmpty())
	{
		mdp = QInputDialog::getText(this, tr("Connexion "),
			tr("Mot de passe :"), QLineEdit::Password, QString(), &ok_mdp);
		if (ok_mdp && !mdp.isEmpty())
		{
			if (!file.open(QIODevice::ReadOnly | QIODevice::Text))  
				return;
			QTextStream flux(&file);
			while(!flux.atEnd())
			{
				ligne = flux.readLine(); 
				info = (QString(ligne).split(" : "));
				if(info[1] == id && info[3] == mdp) //si identifiant et mot de passe concordent, on se connecte
				{
					id_user_actuel = id;
					mdp_user_actuel = mdp;
					fichier_user_actuel = info[7];

					if(info[5] == "n" || info[5] =="N")
						user_actuel_IsAdmin = false;
					else if(info[5] == "o" || info[5] =="O")
						user_actuel_IsAdmin = true;

					QMessageBox* co = new QMessageBox(QMessageBox::NoIcon, tr("Connexion "), "Bienvenue, " + id);
					co->setIconPixmap(QPixmap("Resources/validationConnexion.png"));
					co->show();
					return;
				}
				else if (info[1] == id && info[3] != mdp) //si mot de passe erroné, on affiche un message d'erreur
				{
					QMessageBox* wrong_mdp = new QMessageBox(QMessageBox::NoIcon, tr("Gestion des utilisateurs "), "Erreur, mot de passe invalide !");
					wrong_mdp->setIconPixmap(QPixmap("Resources/erreurConnexion.png"));
					wrong_mdp->show();
					int ret = wrong_mdp->exec();
					if (ret == QMessageBox::Ok)
						Connexion(); //on relance le processus de connexion
				}
			}
			//si on arrive là, ca veut dire que l'identifiant n'existe pas dans notre fichier "Utilisateurs.txt"
			QMessageBox* wrong_id = new QMessageBox(QMessageBox::NoIcon, tr("Gestion des utilisateurs "), "Erreur, identifiant invalide !");
			wrong_id->setIconPixmap(QPixmap("Resources/erreurConnexion.png"));
			wrong_id->show();
			int ret = wrong_id->exec();
			if (ret == QMessageBox::Ok)
				Connexion(); //on relance le processus de connexion
		}
	}
	else
		exit(0);
}

// Enregistrement
void User::Enregistrement()
{
	bool ok_id, ok_mdp, ok_admin;
	QString id, mdp, admin, temp;
	QStringList valide;

	id = QInputDialog::getText(this, tr("Gestion des utilisateurs "),
				tr("Identifiant : "), QLineEdit::Normal, QString(), &ok_id);
	if (ok_id && !id.isEmpty())
	{
		QFile file("Utilisateurs.txt");
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))  
			return;
		QTextStream verif(&file);
		while(!verif.atEnd())
		{
			temp = verif.readLine(); 
			valide = (QString(temp).split(" : "));
			if(valide[1] == id) //si l'identifiant spécifié existe déjà, on sort de la boucle après avoir affiché un message d'erreur
			{
				QMessageBox* user_exists = new QMessageBox(QMessageBox::NoIcon,"Gestion des utilisateurs ", "Erreur lors de la création de l'utilisateur, un utilisateur possédant cet identifiant existe déjà ! ");
				user_exists->setIconPixmap(QPixmap("Resources/erreurConnexion.png"));
				int ret = user_exists->exec();
				if (ret == QMessageBox::Ok)
					Enregistrement(); //on relance le processus d'enregistrement
				user_exists->show();
				break;
			}
		}
		mdp = QInputDialog::getText(this, tr("Gestion des utilisateurs "),
			tr("Mot de passe :"), QLineEdit::Password, QString(), &ok_mdp);
		if (ok_mdp && !mdp.isEmpty())
		{
			admin = QInputDialog::getText(this, tr("Gestion des utilisateurs "),
			tr("Administrateur (O / N) :"), QLineEdit::Normal, QString(), &ok_admin);
			if (ok_admin && !admin.isEmpty())
			{
				if( admin == "O" || admin == "N" || admin == "o" || admin == "n")
				{
					identifiant.push_back(id);
					administrateur.push_back(admin);
					mot_de_passe.push_back(mdp);
					// Création du fichier texte
					QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer l'utilisateur sous", id, "Fichier texte (*.txt)");
					QFileInfo info(fileName);
					QFile fichier_util(fileName);
					// On ouvre notre fichier en écriture
					if (!fichier_util.open(QIODevice::WriteOnly | QIODevice::Text))
						return;

					// Création d'un objet QTextStream à partir de notre objet QFile
					QTextStream flux(&fichier_util);
					flux.setCodec("UTF-8");
					// Écriture des différentes lignes dans le fichier
					flux << "Identifiant : " << id << endl << " Mdp : " << mdp << endl << " Administrateur : " << admin <<endl;
					emplacement_fichier.push_back(fileName);
					QMessageBox* Util = new QMessageBox(QMessageBox::NoIcon,"Gestion des utilisateurs ", "Utilisateur crée avec succès !");
					Util->setIconPixmap(QPixmap("Resources/validationConnexion.png"));
					Util->show();
				}
				else
				{
					QMessageBox* pb = new QMessageBox(QMessageBox::NoIcon,"Gestion des utilisateurs ", "Erreur lors de la création de l'utilisateur, données saisies invalides.");
					pb->setIconPixmap(QPixmap("Resources/erreurConnexion.png"));
					int ret = pb->exec();
					if (ret == QMessageBox::Ok)
						Enregistrement(); //on relance le processus d'enregistrement
					pb->show();
				}

			}
		}
	}
	else if (!ok_id)
		exit(0);
}

// Stockage des utilisateurs crées (au lancement si on s'enregistre et à la fermeture de l'application)
void User::StockageVector()
{
	QFile file("Utilisateurs.txt");
	// On ouvre notre fichier en écriture
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
		return;

	// Création d'un objet QTextStream à partir de notre objet QFile
	QTextStream flux(&file);
	flux.setCodec("UTF-8");
	// Écriture des différentes lignes dans le fichier
	for (int i = 0; i < identifiant.size(); i++)
		flux << "Identifiant : " << identifiant[i] << " : Mdp : " << mot_de_passe[i] << " : Admin : " << administrateur[i] << " : Emplacement : " << emplacement_fichier[i] << endl;
}

// Suppression
void User::RemoveUtil()
{
	if(user_actuel_IsAdmin)
	{
		bool ok, id_correct ;
		QString ligne, temp;
		QStringList info;
		QFile file("Utilisateurs.txt");
		QFile file2("Utilisateurs.txt");
		QString id = QInputDialog::getText(this, tr("Gestion des utilisateurs "),
					tr("Saisissez l'identifiant de l'utilisateur à supprimer : "), QLineEdit::Normal, QString(), &ok);
		if(ok && !id.isEmpty() )
		{
			if (!file.open(QIODevice::ReadWrite | QIODevice::Text))  
				return;
			QTextStream flux(&file);
			//on vérifie que l'identifiant existe dans le fichier
			while(!flux.atEnd())
			{
				ligne = flux.readLine(); 
				info = (QString(ligne).split(" : "));
				if(info[1] == id) //si l'identifiant spécifié est le même que celui de la ligne alors on sort de la boucle
				{
					id_correct = true;
					QFile::remove(info[7]);
					break;
				}
			}
			
			if(!id_correct) //on vérifie que l'utilisateur spécifié n'existe pas non plus dans les qvector (si le logiciel n'a pas été fermé, la sauvegarde dans Utilisateurs.txt n'aura pas été faite)
			{
				for(int i = 0; i < identifiant.size() ; i++)
					{
						if(identifiant[i] == id)
						{
							id_correct = true;
							identifiant.remove(i);
							mot_de_passe.remove(i);
							QFile::remove(emplacement_fichier[i]);
							emplacement_fichier.remove(i);
							administrateur.remove(i);
							break;
						}
					}
			}
			if (id_correct) //si l'identifiant saisi existe
			{
				if (!file2.open(QIODevice::ReadWrite | QIODevice::Text))  
					return;
				QTextStream in(&file2);
				while(!in.atEnd())
				{
					QString line = in.readLine(); 
					info = (QString(line).split(" : "));
					if(info[1] != id) //si l'identifiant spécifié n'est pas le même que celui de la ligne, alors on réécrit la ligne
						temp.append(line + "\n");
				}
				//on resize le fichier (une ligne de moins) et on écrit les identifiants gardés
				file2.resize(0);
				in << temp;
				file2.close();
			
				QMessageBox* suppression_ok = new QMessageBox(QMessageBox::NoIcon, tr("Gestion des utilisateurs "), "La suppression s'est déroulée avec succès. ");
				suppression_ok->setIconPixmap(QPixmap("Resources/supprUti.png"));
				suppression_ok->show();
			}
			else
			{
				QMessageBox* wrong_id = new QMessageBox(QMessageBox::NoIcon, tr("Gestion des utilisateurs "), "Erreur, aucun utilisateur ne correspond à l'identifiant spécifié ! ");
				wrong_id->setIconPixmap(QPixmap("Resources/erreurConnexion.png"));
				wrong_id->show();
				int ret = wrong_id->exec();
				if (ret == QMessageBox::Ok)
					RemoveUtil(); //on relance le processus de suppression
			}
		}
	}
	else
	{
		QMessageBox* notAdmin = new QMessageBox(QMessageBox::NoIcon, tr("Gestion des utilisateurs "), "Erreur, vous devez disposer de droits d'administrateur pour effectuer une telle action.");
		notAdmin->setIconPixmap(QPixmap("Resources/erreurConnexion.png"));
		notAdmin->show();
	}
}