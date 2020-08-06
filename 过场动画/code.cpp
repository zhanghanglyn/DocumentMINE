void ASequencerGenerator::TestSetBind()
{
	if (SequenceAsset == nullptr)
		return;

	TArray<UMovieSceneTrack*> SceneTracks = SequenceAsset->GetMovieScene()->GetMasterTracks();
	for (UMovieSceneTrack* ItemTrack : SceneTracks)
	{
		for (UMovieSceneSection* Section : ItemTrack->GetAllSections())
		{
			//TArray<FGuid> SecBindings;
			//Section->GetReferencedBindings(SecBindings);

			if (const UMovieSceneSubSection* SubSection = Cast<UMovieSceneSubSection>(Section))
			{
				AActor* TestActor = SubSection->GetActorToRecord();
				UMovieSceneSequence* MoveSS = SubSection->GetSequence();
				ULevelSequence* TempLevelSeq = Cast<ULevelSequence>(MoveSS);
				TArray<FMovieSceneBinding> TempBindings = TempLevelSeq->GetMovieScene()->GetBindings();
				//FMovieSceneSequenceID SequenceID = TempLevelSeq->GetMovieScene()->GetUniqueID(); //.GetFocusedTemplateID();
				FMovieSceneSequenceID SequenceID(TempLevelSeq->GetMovieScene()->GetUniqueID());
				FMovieSceneSequenceID SequenceID2(SubSection->GetSequenceID());

				//对所有的binding进行替换
				for (FMovieSceneBinding EachBind : TempBindings)
				{
					FString BindingNmae = EachBind.GetName();
					if (BindingNmae.Equals(PlayerBindID.ToString()))
					{
						ADanteCharacter* DanteCharacter = Cast<ADanteCharacter>(FActorUtility::GetPlayerCharacter(this));
						if (!DanteCharacter->GetBInSequence())
							DanteCharacter->SetInSequence();
						//FMovieSceneObjectBindingID BindID = m_MovieActor->FindNamedBinding(FName(*BindingNmae));// , DanteCharacter);
						//m_MovieActor->AddBindingByTag("Player", DanteCharacter);
						m_MovieActor->AddBinding(FMovieSceneObjectBindingID(EachBind.GetObjectGuid(), SequenceID), DanteCharacter);
					}
				}
				int32 b = 1;
				FString BA = "3";
			}
			if (UMovieSceneActorReferenceSection* SubSection = Cast<UMovieSceneActorReferenceSection>(Section))
			{
				TArray<FGuid> ReferencedBindings;
				SubSection->GetReferencedBindings(ReferencedBindings);
				FMovieSceneActorReferenceData ReferenceData = SubSection->GetActorReferenceData();
				int32 a = 1;
			}

		}
	}

	for (const FMovieSceneBinding& Binding : SequenceAsset->GetMovieScene()->GetBindings())
	{
		FString BindName = Binding.GetName();
		FGuid BindGuid = Binding.GetObjectGuid();
		for (UMovieSceneTrack* Track : Binding.GetTracks())
		{
			// find transform track among all tracks
			UMovieScene3DTransformTrack* TransformTrack = Cast<UMovieScene3DTransformTrack>(Track);
			if (TransformTrack)
			{
				for (const UMovieSceneSection* Section : TransformTrack->GetAllSections())
				{
					const UMovieScene3DTransformSection* TransformSection = Cast<UMovieScene3DTransformSection>(Section);
					//if (TransformSection)
					//{
						//TArrayView<FMovieSceneFloatChannel*> FloatChannels = TransformSection->GetChannelProxy().GetChannels<FMovieSceneFloatChannel>();

					//}
				}
			}
		}
	}
}