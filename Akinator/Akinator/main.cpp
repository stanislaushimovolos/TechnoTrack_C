#include <iostream>
#include <cstring>
#include <windows.h>

#include "../Tree_t/Tree.h"
#include "../Akinator/Akinator.h"


int main () {

	Tree akinTree = {};
	treeConstruct (&akinTree);

	char *buffer = 0;

	readBase (&buffer, inputFilename);

	createBase (buffer, akinTree.root);

	userWorking (&akinTree);

	printTreeFile (&akinTree, outFilename);

	destructTree (&akinTree);

	return 0;
}


void userWorking (const Tree *const tree) {

	int userChoice = 1;

	while (userChoice > 0) {

		printf ("What do you want: "
				        "guess object(%c), "
				        "describe object(%c), "
				        "compare objects (%c) "
				        "exit without saving(%c), "
				        "exit and save (%c)\n",
		        GuessObject, DescribeObj, CompareObj, ExitWithoutSav, ExitSav);

		userChoice = getchar ();

		fflush (stdin);

		switch (userChoice) {

			case GuessObject : {

				guessObject (tree);
				break;
			}

			case ExitWithoutSav: {
				userChoice = 0;
				break;
			}

			case ExitSav: {
				printTreeFile (tree, inputFilename);
				userChoice = 0;
				break;
			}

			case DescribeObj: {

				char target[maxContentLength] = {};
				int NodeCounter = 0;
				Node *CurrentNode = {};
				NodeWay *parentArr = 0;

				nodeConstruct (&CurrentNode);

				printf ("Enter the name\n");

				fgets (target, maxContentLength - 1, stdin);

				target[strlen (target) - 1] = '\0';

				fflush (stdin);

				FILE *voiceFile = fopen ("file.txt", "w");

				fprintf (voiceFile, "%s, ", target);

				if (!(CurrentNode = TreeSearcher (tree, target)))
					printf ("Wrong name of the object\n");


				else {

					fflush (stdin);

					parentArr = createArrOfParents (tree, CurrentNode, &NodeCounter);

					for (int i = NodeCounter; i > 0; i--) {
						if ((parentArr[i]).state == 0) {
							printf (" not  ");
							fprintf (voiceFile, " not  ");
						}
						printf (" %s\n", (parentArr[i]).node->content);
						fprintf (voiceFile, "%s, ", (parentArr[i]).node->content);
					}
					fclose (voiceFile);
					system ("balcon -f \"file.txt\" -w");
				}

				free (parentArr);

				fflush (stdin);

				break;
			}

			case CompareObj: {
				compareObjects (tree);
				break;
			}

			default: {
				printf ("Wrong input, please, try again\n");
				fflush (stdin);
				break;
			}
		}
	}

	dumpTreePicture (tree, outFilenameForDotDump);

	printTree (tree, outFilenameForDotPrint);

	Sleep (350);
}


void guessObject (const Tree *const tree) {

	int TreeAmountCounter = 0;

	const int NodesAmount = tree->nodeAmount;

	char UserChoice = 0;

	Node *currentNode = tree->root;

	while (currentNode && TreeAmountCounter < NodesAmount) {

		printf ("%s? \n",
		        currentNode->content);

		scanf ("%c", &UserChoice);

		fflush (stdin);

		if (UserChoice == positiveAnswer) {
			if (currentNode->Right)
				currentNode = currentNode->Right;

			else break;

		} else if (UserChoice == negativeAnswer) {

			if (currentNode->Left)
				currentNode = currentNode->Left;

			else break;

		} else {
			printf ("Wrong input, please, try again\n");
			continue;
		}

		TreeAmountCounter++;
	}

	if (negativeAnswer == UserChoice)

		addNewObject (currentNode);
}


void addNewObject (Node *negativeUserChoiceCatcher) {

	Node *beginPositiveAnswer = {};
	Node *NewTreeObject = {};

	nodeConstruct (&beginPositiveAnswer);
	nodeConstruct (&NewTreeObject);

	beginPositiveAnswer->content = negativeUserChoiceCatcher->content;

	char *newNodeQuestion = (char *) calloc (maxContentLength, sizeof (char));
	char *newNodeContent = (char *) calloc (maxContentLength, sizeof (char));

	printf ("What was that?\n");

	fflush (stdin);

	fgets (newNodeContent, maxContentLength - 1, stdin);

	newNodeContent[strlen (newNodeContent) - 1] = '\0';

	fflush (stdin);

	printf ("What's the Difference between %s and %s ?\n", newNodeContent, beginPositiveAnswer->content);

	Sleep (1000);

	printf ("it('s)...\n");

	fgets (newNodeQuestion, maxContentLength - 1, stdin);

	newNodeQuestion[strlen (newNodeQuestion) - 1] = '\0';

	fflush (stdin);

	nodeSetName (NewTreeObject, newNodeContent);
	nodeSetName (negativeUserChoiceCatcher, newNodeQuestion);

	connectLeft (negativeUserChoiceCatcher, beginPositiveAnswer);
	connectRight (negativeUserChoiceCatcher, NewTreeObject);
}


bool compareObjects (const Tree *const tree) {

	char target[maxContentLength] = {};

	Node *FirstObj = {};

	printf ("Enter the first name\n");

	fgets (target, maxContentLength - 1, stdin);

	target[strlen (target) - 1] = '\0';

	fflush (stdin);

	if (!(FirstObj = TreeSearcher (tree, target))) {
		printf ("Wrong name of the object\n");
		return 1;
	}

	for (int i = 0; i < maxContentLength; i++)
		target[i] = 0;

	Node *SecondObj = {};

	printf ("Enter the second name\n");

	fgets (target, maxContentLength - 1, stdin);

	target[strlen (target) - 1] = '\0';

	fflush (stdin);

	if (!(SecondObj = TreeSearcher (tree, target))) {
		printf ("Wrong name of the object\n");
		return 1;
	}

	if (SecondObj->content == FirstObj->content) {
		printf ("it is the same object\n");
		return 0;
	}

	int FirstCounter = 0, SecondCounter = 0, MainNodeCounter = 0;

	NodeWay *parentArrFirst = 0;
	NodeWay *parentArrSecond = 0;

	parentArrFirst = createArrOfParents (tree, FirstObj, &FirstCounter);
	parentArrSecond = createArrOfParents (tree, SecondObj, &SecondCounter);

	FILE *voiceFile = fopen ("file.txt", "w");

	fprintf (voiceFile, "%s, ", FirstObj->content);
	fprintf (voiceFile, "%s, ", SecondObj->content);

	printf ("common qualities:\n");
	fprintf (voiceFile, "common qualities:");

	if (parentArrFirst->node->Parent && parentArrSecond->node->Parent) {

		while ((parentArrFirst[FirstCounter - MainNodeCounter - 1].node->content) ==
		       (parentArrSecond[SecondCounter - MainNodeCounter - 1].node->content)) {

			if ((parentArrFirst[FirstCounter - MainNodeCounter]).state == 0) {
				printf (" not  ");
				fprintf (voiceFile, " not  ");
			}
			printf (" %s\n",
			        (parentArrFirst[FirstCounter - MainNodeCounter]).node->content);
			fprintf (voiceFile, " %s\n",
			         (parentArrFirst[FirstCounter - MainNodeCounter]).node->content);

			MainNodeCounter++;
		}
	}


	printf ("But %s : \n", FirstObj->content);
	fprintf (voiceFile, "But %s : \n", FirstObj->content);

	for (int i = FirstCounter - MainNodeCounter; i > 0; i--) {
		if ((parentArrFirst[i]).state == 0) {
			fprintf (voiceFile, " not  ");
			printf (" not  ");
		}

		printf (" %s\n", (parentArrFirst[i]).node->content);
		fprintf (voiceFile, "%s, ", (parentArrFirst[i]).node->content);
	}

	fprintf (voiceFile, "And %s : \n", SecondObj->content);
	printf ("And %s : \n", SecondObj->content);

	for (int i = SecondCounter - MainNodeCounter; i > 0; i--) {
		if ((parentArrSecond[i]).state == 0) {
			fprintf (voiceFile, " not  ");
			printf (" not  ");
		}
		printf (" %s\n", (parentArrSecond[i]).node->content);
		fprintf (voiceFile, "%s, ", (parentArrSecond[i]).node->content);
	}

	fclose (voiceFile);
	system ("balcon -f \"file.txt\" -w");

	free (parentArrFirst);
	free (parentArrSecond);
}
