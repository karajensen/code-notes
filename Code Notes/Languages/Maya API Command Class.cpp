///////////////////////////////////////////////////////////////////////////////////////////////////////
//COMMAND CLASS TEMPLATE
///////////////////////////////////////////////////////////////////////////////////////////////////////
//Calling commands in Maya: Maya creates an instance of the class through Creator then doIt function
//If undoable is false, the destructor is called. If undoable is true, instance placed on undo queue
//If undo is used, undoIt is called. If redo is used, redoIt is called
//isUndoable automatically returns false. Command that isn't undoable is called an Action.
//doIt function sets up the command, the redoIt executes the command

//SIMPLE COMMAND CLASS
//use at top of .ccp file, fill in do it function for simple commnd (non-undoable)
DeclareSimpleCommand(CommandName, "Creator", "1.0"); 

//--------------------------------------------------------------------------------------------
//COMMAND CLASS
//--------------------------------------------------------------------------------------------
class MyCommand : public MPxCommand
{
private:

	enum { QueryMode, CreationMode, EditMode };
	struct CommandFlag
	{
		char *number, *numberLong;
		char *help,	  *helpLong;
		CommandFlag()
		{
			number = "-n";	numberLong = "-number";
			help = "-he";	helpLong = "-help";
		}
	};

	int state;
	MDGModifier dgMod;
	static CommandFlag flag;

public: 
	virtual MStatus undoIt();
	virtual MStatus redoIt();
	virtual bool isUndoable() const;
	virtual MStatus doIt(const MArgList& args);

	static void* creator(){ return new MyCommand; }
	static MSyntax newSyntax();
};
//---------------------------------------------------------------------------------------------
//FLAG INITIALISING
//---------------------------------------------------------------------------------------------
MyCommand::CommandFlag MyCommand::flag;
MSyntax MyCommand::newSyntax()
{
	//syntax object automatically creates help text/does error checking for type
	//use a help flag to customize what this says in script editor
	MSyntax syntax;
	syntax.addFlag(flag.number, flag.numberLong, MSyntax::kLong);
	syntax.addFlag(flag.help, flag.helpLong);
	syntax.enableQuery(true);
	syntax.enableEdit(true);
	return syntax;
}
//---------------------------------------------------------------------------------------------
//ON COMMAND
//---------------------------------------------------------------------------------------------
MStatus MyCommand::doIt(const MArgList& args)
{
	//Check flags are valid
	MStatus stat;
	MArgDatabase argData(syntax(), args, &stat);
	if(!stat){ return stat; }

	//check state
	if(argData.isQuery())
		state = QueryMode;
	else if(argData.isEdit())
		state = EditMode;
	else
		state = CreationMode;

	//check if help is set if using custom help
	if(argData.isFlagSet(flag.help))
		setResult("This is a short description of how the plugin works");

	//IN CREATION/EDIT STATE
	if(state != QueryMode)
	{
		//get flags
		int Number;
		if(argData.isFlagSet(flag.number))
			argData.getFlagArgument(flag.number, 0, Number);

		//do commands
		dgMod.commandToExecute("cylinder");
		return redoIt();

	}
	else //IN QUERY STATE
	{
		if(argData.isFlagSet(flag.number))
			MGlobal::displayInfo("The value is...");
	}
	return MS::kSuccess;
}
//---------------------------------------------------------------------------------------------
//ON REDO
//---------------------------------------------------------------------------------------------
MStatus MyCommand::redoIt()
{
	//executes the saved commands
	return dgMod.doIt();
}
//---------------------------------------------------------------------------------------------
//ON UNDO
//---------------------------------------------------------------------------------------------
MStatus MyCommand::undoIt()
{
	//undos the saved commands
	return dgMod.undoIt();
}
//---------------------------------------------------------------------------------------------
//IS UNDOABLE
//---------------------------------------------------------------------------------------------
bool MyCommand::isUndoable() const
{
	//query mode doesn't edit Maya scene 
	if(state == QueryMode)
		return false;
	return true;
}
//=============================================================================================
//INITIALISE PLUGIN
//=============================================================================================
MStatus initializePlugin(MObject obj)
{
	//initialise command
	MFnPlugin pluginFn(obj,"VendorName", "1.0");
	MStatus stat = pluginFn.registerCommand("CommandName", MyCommand::creator, MyCommand::newSyntax);
	if(!stat){ stat.perror("Register of 'CommandName' failed"); }

	return stat;
}
//=============================================================================================
//UNINITIALISE PLUGIN
//=============================================================================================
MStatus uninitializePlugin(MObject obj)
{
	//unitialise command
	MFnPlugin pluginFn(obj);
	MStatus stat = pluginFn.deregisterCommand("CommandName");
	if(!stat){ stat.perror("Deregister of 'CommandName' failed"); }

	return stat;
}