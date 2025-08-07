"use client";

import { useSearchParams } from "next/navigation";
import ReviewForm from "@/components/ReviewForm";

interface ReviewFormWrapperProps {
  courses: any[];
}

export function ReviewFormWrapper({ courses }: ReviewFormWrapperProps) {
  const searchParams = useSearchParams();
  const prefillCourseId = searchParams.get("courseId");

  return <ReviewForm courses={courses} prefillCourseId={prefillCourseId} />;
}
